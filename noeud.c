/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "noeud.h"

/* FONCTIONS =========================================================== */

/* Taille (en octets) du champs data */
size_t size_data(node* n){
	return (n->len)*sizeof(align_data) - sizeof(*n);
}

/* Taille (en nombre de blocs) du champs data */
size_t nb_blocs_data(node* n){
	return nb_blocs(size_data(n));
}

/* Taille (en nombre de blocs) de l'en-tête */
size_t nb_blocs_node(){
	return nb_blocs(sizeof(node));
}

/* 1 si le noeud a un successeur, 0 sinon */
short has_next(node* n){
	if (n==NULL) return 0;
	return ( (n->next) != 0 ) ;
}

/*************************************************************************/
