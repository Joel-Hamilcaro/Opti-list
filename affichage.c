/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "affichage.h"
#include <stdio.h>

/* FONCTIONS D'AFFICHAGE =============================================== */
/* ===================================================================== */

/* Affichage des tranches */
static void print_tranches(tranche* t){
	printf("Tableau de tranche :\n");
	for (int i=0; t[i].decalage>ID_VIDE && i<NTRANCHES ; i++){
		printf( "\t[%ld;%ld]\n",t[i].decalage,t[i].nb_blocs);
	}
}

/* Affichage d'un noeud */
static void print_node(node* n, int pos){
	printf("[%+6ld  (%6ld)   \t",n->next,pos+n->next);
	printf("%+6ld  (%6ld)   \t",n->previous,pos+n->previous);
	printf("%6ld  \t",n->len);
	printf("%6ld ]\n",nb_blocs_data(n));
}

/* Affichage d'un noeud classique */
static void print_cld_node(cld_node* n){
	printf("[%15p \t",n->next);
	printf("%15p \t",n->previous);
	printf("%15ld ]\n",n->nb_blocs_data);
}

/* Affichage d'une liste */
static void print_list(head* liste){
	printf("Affichage de la liste :\n\n");
	node* n = ld_first(liste);
	int pos = liste->first;
	if (n==NULL){
		printf(" LISTE VIDE \n\n");
		return;
	}
	printf("          BLOC       \t  NEXT              \tPREVIOUS        \tLEN     \tNBDATA\n\n");
	int ord = 0;
	printf("%6d - Bloc %6d \t",ord,pos);
	print_node(n,pos);
	pos += n->next;
	while (has_next(n)) {
		n = (node*)ld_next(liste, n);
		ord++;
		printf("%6d - Bloc %6d \t",ord,pos);
		print_node(n,pos);
		pos += n->next;
	}
	printf("\n");
}

/* Affichage d'une liste */
static void print_cld_list(cld_head* liste){
	printf("Affichage de la liste :\n\n");
	cld_node* n = liste->first;
	if (n==NULL){
		printf(" LISTE VIDE \n\n");
		return;
	}
	printf("\t\tADRESSE\t\t\tNEXT\t\t\tPREVIOUS\t\tNBDATA\n\n");
	int ord = 0;
	printf("%6d - Adr. %p \t",ord,n);
	print_cld_node(n);
	while (n->next!=NULL) {
		n = n->next;
		ord++;
		printf("%6d - Adr. %p \t",ord,n);
		print_cld_node(n);
	}
	printf("\n");
}

/* Affichage d'un head */
static void print_head(head* l){
	printf("Adresse du \"HEAD\" :\n\t %p \n",l);
	printf("Adresse de MEMORY :\n\t %p \n",(l->memory));
	printf("Position FIRST :\n\t %ld \n",(l->first));
	printf("Position LAST :\n\t %ld \n",(l->last));
	printf("Adresse du tableau de tranche :\n\t %p \n",(l->libre));
	printf("Adresse du FIRST :\n\t %p \n", ld_first(l));
	printf("Adresse du LAST :\n\t %p \n",ld_last(l));
	printf("Longueur de la liste :\n\t %ld \n",(l->length));
	printf("Nombre de blocs alloués :\n\t %ld \n",(l->allocated_blocs));
}

/* Affichage d'un head */
static void print_cld_head(cld_head* l){
	printf("Adresse du \"HEAD\" :\n\t %p \n",l);
	printf("Adresse FIRST :\n\t %p \n",(l->first));
	printf("Adresse LAST :\n\t %p \n",(l->last));
	printf("Longueur de la liste :\n\t %ld \n",(l->length));
}
/* Affichage de l'opération insert_first lors des tests */
void print_insert_first(size_t cb_blocs){
	printf("--------------------------------------------------------------------------------------------------\n");
	printf("                           INSERTION DATA %ld OCTETS  (  %ld blocs)                               \n",(cb_blocs)*sizeof(align_data),(cb_blocs));
	printf("                                     (position : first)                                           \n");
	printf("--------------------------------------------------------------------------------------------------\n");
}

/* Affichage de l'opération insert_last lors des tests */
void print_insert_last(size_t cb_blocs){
	printf("--------------------------------------------------------------------------------------------------\n");
	printf("                           INSERTION DATA %ld OCTETS  ( %ld blocs)                              \n",(cb_blocs)*sizeof(align_data),(cb_blocs));
	printf("                                     (position : last)                                            \n");
	printf("--------------------------------------------------------------------------------------------------\n");
}

/* Affichage de l'opération insert_before lors des tests */
void print_insert_before(size_t cb_blocs, size_t pos){
	printf("--------------------------------------------------------------------------------------------------\n");
	printf("                           INSERTION DATA %ld OCTETS  (  %ld blocs)                               \n",(cb_blocs)*sizeof(align_data),(cb_blocs));
	printf("                                        (avant : %ld)                                             \n",pos);
	printf("--------------------------------------------------------------------------------------------------\n");
}

/* Affichage de l'opération insert_after lors des tests */
void print_insert_after(size_t cb_blocs, size_t pos){
	printf("--------------------------------------------------------------------------------------------------\n");
	printf("                           INSERTION DATA %ld OCTETS  (  %ld blocs)                               \n",(cb_blocs)*sizeof(align_data),(cb_blocs));
	printf("                                        (après : %ld)                                             \n",pos);
	printf("--------------------------------------------------------------------------------------------------\n");
}

/* Affichage de l'opération delete_node lors des tests */
void print_delete_node(size_t pos){
	printf("==================================================================================================\n");
	printf("                                       SUPPRESSION                                                \n");
	printf("                                      (noeud : %ld)                                               \n",pos);
	printf("==================================================================================================\n");
}

/* Affichage la mémoire libre */
static void print_total_free(head* l){
	size_t tfm = ld_total_free_memory(l);
	printf("Mémoire libre :\v%ld octets (%ld blocs)\n",tfm,nb_blocs(tfm));
}

/* Affichage la mémoire libre */
static void print_total_useful(head* l){
	size_t tfm = ld_total_useful_memory(l);
	printf("Mémoire utile :\v%ld octets (%ld blocs)\n",tfm,nb_blocs(tfm));
}

/* Affichage de toutes les informations concernant la liste en cours */
void print_all(head* l){
	printf("\n\n");
	print_head(l);
	printf("\n\n");
	print_tranches((l->libre));
	printf("\n\n");
	print_total_free(l);
	print_total_useful(l);
	printf("\n\n");
	print_list(l);
	printf("\n\n");
}

void print_cld_all(cld_head* l){
	printf("\n\n");
	print_cld_head(l);
	printf("\n\n");
	print_cld_list(l);
	printf("\n\n");
}

/* Affichage de toutes les informations initiales (avant toute opération) */
void print_initialisation(head* l, size_t octets){
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("--------------------------------------------------------------------------------------------------\n");
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("-------------------------------------- INFORMATIONS GENERALES  -----------------------------------\n");
	printf("Taille d'un bloc \v%ld octets\n",sizeof(align_data));
	printf("Taille d'un noeud (en-tête)\v%ld octets \n",sizeof(node));
	printf("Taille d'un noeud (en-tête)\v%ld blocs \n\n",nb_blocs_node());
	printf("----------------------------------------- NOTRE EXEMPLE ------------------------------------------\n");
	printf("Mémoire demandée \v%ld octets\n",octets);
	printf("Blocs à allouer \v%ld blocs = %ld octets \n",nb_blocs(octets),nb_blocs(octets)*sizeof(align_data));
	printf("---------------------------------------- LISTE INITIALE ------------------------------------------\n");
	print_all(l);
}

/* Affichage de toutes les informations initiales (avant toute opération) */
void print_cld_initialisation(cld_head* l){
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("--------------------------------------------------------------------------------------------------\n");
	//printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("-------------------------------------- INFORMATIONS GENERALES  -----------------------------------\n");
	printf("Taille d'un bloc \v%ld octets\n",sizeof(align_data));
	printf("---------------------------------------- LISTE INITIALE ------------------------------------------\n");
	print_cld_all(l);
}

/* Affichage de toutes les informations après destruction de la liste */
void print_destroy(head* l){
	printf("--------------------------------------- DESTRUCTION  ---------------------------------------------\n");
	printf("Adresse de HEAD :\v%p \n\n",l);
	printf("__________________________________________________________________________________________________\n");
}


/*************************************************************************/
