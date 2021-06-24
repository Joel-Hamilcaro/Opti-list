/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "tests.h"
#include <stdlib.h>
#include <stdio.h>

/* FONCTIONS =========================================================== */

/* Noeud à la position k */
static node* ld_get_node(head* l, size_t k){
	node* n = ld_first(l);
	for (int i=0; i<k; i++){
		if (has_next(n)) n = (node*)ld_next(l, n);
		else return NULL;
	}
	return n;
}

/* Noeud à la position k */
static cld_node* cld_get_node(cld_head* l, size_t k){
	cld_node* n = l->first;
	if (n==NULL) return NULL;
	for (int i=0; i<k; i++){
		if (n->next!=NULL) n = n->next;
		else return NULL;
	}
	return n;
}

/* Exécution d'une insertion aléatoire dans une liste. affiche
   sert de booléen pour savoir si on affiche les opérations ou non */
static void random_insert(void* l, short affiche, size_t length, size_t pos, short classic){
	int val = random()%100;
	void* p_data = &val;
	size_t cb_blocs = random()%10;
	pos--;
	if (pos==-1){
		if (classic) cld_insert_first(((cld_head*)l),(cb_blocs)*sizeof(align_data),p_data);
		else ld_insert_first(((head*)l),(cb_blocs)*sizeof(align_data),p_data);
		if (affiche==2) print_insert_first(cb_blocs);
	}
	else if (pos==length){
		if (classic) cld_insert_last(((cld_head*)l),(cb_blocs)*sizeof(align_data),p_data);
		else ld_insert_last(((head*)l),(cb_blocs)*sizeof(align_data),p_data);
		if (affiche==2) print_insert_last(cb_blocs);
	}
	else {
		short before_n = random()%2;
		if (before_n || pos==0){
			if (classic){
				cld_node* n = cld_get_node(((cld_head*)l),pos);
				cld_insert_before(((cld_head*)l),n,(cb_blocs)*sizeof(align_data),p_data);
			}
			else {
				node* n = ld_get_node(((head*)l),pos);
				ld_insert_before(((head*)l),n,(cb_blocs)*sizeof(align_data),p_data);
			}
			if (affiche==2) print_insert_before(cb_blocs,pos);
		}
		else {
			if (classic){
				cld_node* n = cld_get_node(((cld_head*)l),pos-1);
				cld_insert_after(((cld_head*)l),n,(cb_blocs)*sizeof(align_data),p_data);
			}
			else {
				node* n = ld_get_node(((head*)l),pos-1);
				ld_insert_after(((head*)l),n,(cb_blocs)*sizeof(align_data),p_data);
			}
			if (affiche==2) print_insert_after(cb_blocs,pos);
		}
	}
}

/* Exécution d'une opération aléatoire sur une liste.
  affiche sert de booléen pour savoir si on affiche les opérations
  ou non */
static void random_oper(void* l, short affiche, short classic){
	size_t length;
	if (classic){
			length = ((cld_head*)l)->length;
	} else {
			length = ((head*)l)->length;
	}
	size_t oper = random()%4;
	size_t pos = length>0 ? random()%length : 0;
	if (oper>0 || length<=0){
		random_insert(l,affiche,length,pos,classic);
	}
	else {
		if (classic){
			cld_node* n = cld_get_node(((cld_head*)l),pos);
			cld_delete_node(((cld_head*)l),n);
		}
		else {
			node* n = ld_get_node(((head*)l),pos);
			ld_delete_node(((head*)l),n);
		}
		if (affiche==2) print_delete_node(pos);
	}
}

/* Fonction de test */
void test(size_t octets,int loop, short affiche, short classic){
	printf("==================================================================================================\n");
	if (classic)
	printf("                                        TEST LISTE CLASSIQUE                                      \n");
	else
	printf("                                       TEST L3 PROJET C 2019                                      \n");
	printf("==================================================================================================\n");
	void * l;
	if (classic) l = cld_create(NULL,NULL);
	else l = ld_create(octets);
	if (affiche==2){
		if (classic) print_cld_initialisation(((cld_head*)l));
		else print_initialisation(((head*)l),octets);
	}
	if (affiche<2) printf("Opérations en cours ... \n");
	for (long i=0; i<loop; i++){
		random_oper(l,affiche,classic);
		if (affiche==2){
			if (classic) print_cld_all(((cld_head*)l));
			else print_all(((head*)l));
		}
		if ( ( affiche<2 && loop>=10000 && i%(loop/100)==0 && i>0 && i<loop-1)) printf("\t%2.f %%\n",100.0*i/(loop+0.0));
	}
	if (affiche==1){
		if (classic) print_cld_all(((cld_head*)l));
		else print_all(((head*)l));
	}
	printf("=========================================== FIN ==================================================\n");
	if (classic) cld_destroy(((cld_head*)l));
	else ld_destroy(((head*)l));
	l = NULL;
	if (affiche > 0){
		print_destroy(l);
	}
}

/*************************************************************************/
