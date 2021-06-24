/*************************************************************************/
#ifndef AFFICHAGE_H
#define AFFICHAGE_H
/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "projet2019.h"
#include "classique.h"

/* FONCTIONS D'AFFICHAGE =============================================== */
/* ===================================================================== */

/* Affichage de l'opération insert_first lors des tests */
void print_insert_first(size_t cb_blocs);

/* Affichage de l'opération insert_last lors des tests */
void print_insert_last(size_t cb_blocs);

/* Affichage de l'opération insert_before lors des tests */
void print_insert_before(size_t cb_blocs, size_t pos);

/* Affichage de l'opération insert_after lors des tests */
void print_insert_after(size_t cb_blocs, size_t pos);

/* Affichage de l'opération delete_node lors des tests */
void print_delete_node(size_t pos);

/* Affichage de toutes les informations concernant la liste en cours */
void print_all(head* l);

/* Affichage de toutes les informations initiales */
void print_initialisation(head* l, size_t octets);

/* Affichage de toutes les informations après destruction de la liste */
void print_destroy(head* l);

/* Affichage de toutes les informations initiales (liste classique)*/
void print_cld_initialisation(cld_head* l);

/* Affichage de toutes les informations concernant la liste en cours */
/*  (liste classique) */
void print_cld_all(cld_head* l);

/*************************************************************************/
#endif
/*************************************************************************/
