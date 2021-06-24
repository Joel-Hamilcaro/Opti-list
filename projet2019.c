/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "projet2019.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

/* FONCTIONS =========================================================== */

/* 1 si la liste est vide, 0 sinon */
static size_t is_empty(void* liste){
	return (((head*)liste)->first == ID_VIDE);
}

/* trouver le numéro du bloc de n en commençant par memory */
static ptrdiff_t which_bloc(head* l, node* n){
	return (align_data*)n-(align_data*)(l->memory);
}

/* 2.2.1 */
void* ld_create(size_t nboctets){
	head* l = malloc(sizeof(head));
	assert (l!=NULL);
	if (nboctets<10*sizeof(align_data)) nboctets = 10*sizeof(align_data);
	size_t real_memory = nb_blocs(nboctets);
	l -> memory = malloc(real_memory*sizeof(align_data));
	l -> first = ID_VIDE;
	l -> last = ID_VIDE;
	l -> libre = malloc( NTRANCHES *sizeof(tranche) ) ;
	assert(l->libre != NULL && l->memory != NULL);
	init_tranches(l->libre);
	(l -> libre)[0].decalage = 0;
	(l -> libre)[0].nb_blocs = real_memory;
	l -> allocated_blocs = real_memory;
	l -> length = 0;
	return l;
}

/* 2.2.2 */
void* ld_first(void* liste){
	if (liste==NULL || is_empty(liste)) return NULL;
	ptrdiff_t x = ((head*)liste) -> first;
	align_data* p = ( ((head*)liste) -> memory );
	return p + x ;
}

/* 2.2.3 */
void* ld_last(void* liste){
	if (liste==NULL || is_empty(liste)) return NULL;
	ptrdiff_t x = ((head*)liste) -> last;
	align_data* p = ( ((head*)liste) -> memory );
	return p + x ;
}

/* 2.2.4 */
void* ld_next(void* liste, void* current){
	if (liste==NULL || current == NULL || current==ld_last(liste) || is_empty(liste)){
		return NULL;
	}
	if (liste==current){
		return ld_first(liste);
	}
	return ((align_data*)current) + (((node*)current)->next);
}

/* 2.2.5 */
void* ld_previous(void* liste, void* current){
	if (liste==NULL || current == NULL || liste==current || current==ld_first(liste) || is_empty(liste)) return NULL;
	return ((align_data*)current) + (((node*)current)->previous);
}

/* 2.2.6 */
void ld_destroy(void* liste){
	if (liste==NULL) return;
	if (((head*)liste)->memory!=NULL) free(((head*)liste)->memory);
	((head*)liste)->memory = NULL;
	if (((head*)liste)->libre!=NULL) free(((head*)liste)->libre);
	((head*)liste)->libre = NULL;
	free(liste);
}

/* 2.2.7 */
size_t ld_get(void *liste, void *current, size_t len , void *val){
		if (liste==NULL || current==NULL || len==0 || val==NULL) return 0;
		size_t taille_data = size_data(current);
		if (taille_data<=len ){
			memmove(val, (((node*)current)-> data),taille_data);
			return taille_data;
		}
		memmove (val, (((node*)current)-> data),len);
		return len;
}

/* 2.3.1 */
size_t ld_total_free_memory(void* liste){
	if (liste==NULL) return 0;
	size_t st=0;
	tranche * t = (( head *)liste)->libre;
	for (int i =0;i<NTRANCHES && t[i].nb_blocs>0 ;i++){
		st = st + (t[i].nb_blocs);
	}
	return st*sizeof(align_data);
}

/* 2.3.2 */
size_t ld_total_useful_memory(void* liste){
	if (liste==NULL) return 0;
	size_t st =0;
	tranche * t = (( head *)liste)->libre;
	for (int i =0;i<NTRANCHES && t[i].nb_blocs>0  ;i++){
		if ((t[i].nb_blocs)>nb_blocs_node()){
			st = st + (t[i].nb_blocs);
		}
	}
	return st*(sizeof(align_data));
}

/* 2.3.3 */
void* ld_add_memory(void* liste, size_t nboctets){
	if (liste==NULL) return NULL;
	void* ptr = ((head*)liste)->memory;
	size_t blc_mem = ((head*)liste)->allocated_blocs;
	size_t blc_add = nb_blocs(nboctets);
	void* new_ptr = realloc(ptr, (blc_mem+blc_add)*sizeof(align_data) );
	if (new_ptr==NULL) return NULL;
	((head*)liste)->memory = new_ptr;
	add_tranche( ((head*)liste)->libre , blc_add, blc_mem);
	((head*)liste)->allocated_blocs = blc_mem+blc_add;
	return liste;
}

/* 2.3.4 */
void *ld_compactify(void *liste){
	if (liste==NULL) return NULL;
	size_t blc = ( (head*)liste ) -> allocated_blocs;
	void* new_ptr = malloc(blc*sizeof(align_data));
	if (new_ptr==NULL) return NULL;
	ptrdiff_t dec = 0;
	ptrdiff_t prev = 0;
	node* n_copie;
	for ( node* n=ld_first(liste) ; n!=NULL ; n=ld_next(liste,n) ){
		size_t len = (n->len);
		n_copie = memmove(new_ptr,n,sizeof(align_data)*len);
		n_copie->next = (n->len);
		n_copie->previous = prev;
		dec += len;
		blc -= len;
		prev = -len;
		new_ptr = (align_data*)new_ptr+len;
	}
	n_copie->next = 0;
	void* tmp = ((head*)liste)->memory;
	((head*)liste)->memory = (align_data*)new_ptr-dec;
	free(tmp);
	tmp = NULL;
	(((head*)liste) -> first) = 0;
	(((head*)liste) -> last) = dec-(n_copie->len);
	init_tranches(((head*)liste)->libre);
	(((head*)liste) -> libre)[0].decalage = dec;
	(((head*)liste) -> libre)[0].nb_blocs = blc;
	return liste;
}

static head* manage_memory(head* liste){
	if (liste==NULL) return NULL;
	if (nb_tranches(liste->libre)>NTRANCHES/2){
		printf("---> COMPACTIFY\n");
		return ld_compactify(liste);
	}
	if (ld_total_free_memory(liste)<sizeof(align_data)*(liste->allocated_blocs)/10){
		printf("---> ADD MEMORY\n");
		return ld_add_memory(liste,sizeof(align_data)*(liste->allocated_blocs));
	}
	return liste;
}

/* 2.2.8 */
void* ld_insert_first(void *liste, size_t len, void* p_data){
	if (liste==NULL || p_data==NULL) return NULL;
	len = nb_blocs(len+sizeof(node)); 	/* conversion en nombre de blocs */
	ptrdiff_t decalage = use_tranche( (( head* )liste)->libre , len ); /* recherche et m.a.j. des tranches */
	if (decalage==ID_VIDE){
		return NULL;
	}
	/* nouveau noeud n */
	node* n = (node*)( ( (align_data*) ( ((head*)liste) ->memory) ) + decalage );
	if (is_empty(liste)){
		n->next = 0; 	/* init next de n */
		((head*)liste)->last = decalage; 	/* m.a.j. du last de la liste */
	} else {
		node* f = (node*) ld_first(liste);
		n->next = (((head*)liste)->first) - decalage; /* init du next de n */
		f->previous = decalage - (((head*)liste)->first); 	/* m.a.j. du previous de l'ancien first */
	}
	n->previous = 0; 	/* init du previous de n */
	n->len = len; /* init len de n */
	memmove( (node*)n+1 , p_data, size_data(n) ); /* copie des data */
	((head*)liste)->first = decalage; /* m.a.j. du first de la liste */
	((head*)liste)->length++;
	manage_memory(liste);
	return n;
}

/* 2.2.9 */
void* ld_insert_last(void* liste, size_t len, void* p_data){
	if (liste==NULL || p_data==NULL) return NULL;
	len = nb_blocs(len+sizeof(node)); 	/* conversion en nombre de blocs */
	ptrdiff_t decalage = use_tranche( (( head* )liste)->libre , len ); /* recherche et m.a.j. des tranches */
	if (decalage==ID_VIDE){
		return NULL;
	}
	/* nouveau noeud n */
	node* n = (node*)( ( (align_data*) ( ((head*)liste) ->memory) ) + decalage );
	n->next = 0; 	/* init next de n */
	if (is_empty(liste)){
		n->previous = 0; /* init previous de n */
		((head*)liste)->first = decalage; /* m.a.j. du first de la liste */
	} else {
		node* f = (node*) ld_last(liste);
		n->previous = (((head*)liste)->last) - decalage; /* init previous de n */
		f->next = decalage - (((head*)liste)->last); /* m.a.j. next de l'ancien last */
	}
	n->len = len; /* init len de n */
	memmove( (node*)n+1 , p_data, size_data(n) ); /* copie des data */
	((head*)liste)->last = decalage; 	/* m.a.j. du last de la liste */
	((head*)liste)->length++;
	manage_memory(liste);
	return n;
}

/* 2.2.10 */
void* ld_insert_before(void* liste, void* n, size_t len, void* p_data){
	if (liste==NULL || p_data==NULL) return NULL;
	if (((node*)n)->previous==0) return ld_insert_first(liste,len,p_data); /* cas n first */
	len = nb_blocs(len+sizeof(node)); 	/* conversion en nombre de blocs */
	ptrdiff_t decalage = use_tranche( (( head* )liste)->libre , len ); /* recherche et m.a.j. des tranches */
	if (decalage==ID_VIDE){
		return NULL;
	}
	/* Nouveau noeud n2 */
	/* np n ---> np n2 n */
	node* n2 = (node*)( ( (align_data*) ( ((head*)liste) ->memory) ) + decalage );
	node* np = ld_previous(liste,n);
	n2->next = ((which_bloc(liste,(node*)n))) - decalage; /* n2.next = n */
	((node*)n)->previous = decalage - (which_bloc(liste,(node*)n)); /* n.pre = n2 */
	n2->previous = ((which_bloc(liste,(node*)np))) - decalage; /* n2.pre = np */
	((node*)np)->next = decalage - (which_bloc(liste,(node*)np)); /* np.next = n2 */
	n2->len = len; /* init len de n2 */
	memmove( (node*)n2+1 , p_data, size_data(n2) ); /* copie des data */
	((head*)liste)->length++;
	manage_memory(liste);
	return n2;
}

/* 2.2.11 */
void* ld_insert_after(void* liste, void* n, size_t len, void* p_data){
	if (liste==NULL || p_data==NULL || n==NULL) return NULL;
	if (((node*)n)->next==0) return ld_insert_last(liste,len,p_data);	/* cas n last */
	len = nb_blocs(len+sizeof(node));	/* conversion en nombre de blocs */
	ptrdiff_t decalage = use_tranche( (( head* )liste)->libre , len ); /* recherche et m.a.j. des tranches */
	if (decalage==ID_VIDE){
		return NULL;
	}
	/* Nouveau noeud n2 */
	/* But : n nn ---> n n2 nn */
	node* n2 = (node*)( ( (align_data*) ( ((head*)liste) ->memory) ) + decalage );
	node* nn = ld_next(liste,n);
	n2->next = ((which_bloc(liste,(node*)nn))) - decalage;
	((node*)nn)->previous = decalage - (which_bloc(liste,(node*)nn));
	n2->previous = ((which_bloc(liste,(node*)n))) - decalage;
	((node*)n)->next = decalage - (which_bloc(liste,(node*)n));
	n2->len = len;
	memmove( (node*)n2+1 , p_data, size_data(n2) );
	((head*)liste)->length++;
	manage_memory(liste);
	return n2;
}

/* 2.3 */
void* ld_delete_node(void* liste, void* n){
	if (liste==NULL || n==NULL) return NULL;
	add_tranche((( head* )liste)->libre,((node*)n)->len,which_bloc(liste,n));
	// But : np n nn --> n nn */
	node* np = ld_previous(liste,n);
	node* nn = ld_next(liste,n);
	if (np==NULL && nn==NULL){
		((head*)liste)->first = ID_VIDE;
		((head*)liste)->last = ID_VIDE;
		((head*)liste)->length--;
		return liste;
	}
	if (np==NULL){
		((head*)liste)->first = which_bloc(liste,nn);
		nn->previous = 0;
		((head*)liste)->length--;
		return liste;
	}
	if (nn==NULL){
		((head*)liste)->last = which_bloc(liste,np);
		np->next = 0;
		((head*)liste)->length--;
		return liste;
	}
	np->next += ((node*)n)->next;
	nn->previous += ((node*)n)->previous;
	((node*)n)->next = 0;
	((node*)n)->previous = 0;
	((head*)liste)->length--;
	return liste;
}


/*************************************************************************/
