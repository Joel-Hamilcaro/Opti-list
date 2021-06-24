/*************************************************************************/
#ifndef NOEUD_H
#define NOEUD_H
/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "alignement.h"

/* STRUCTURES ========================================================== */

typedef struct {
  ptrdiff_t next;
  ptrdiff_t previous;
  size_t len;
  align_data data[];
} node;

/* FONCTIONS =========================================================== */

/* Taille (en octets) du champs data */
extern size_t size_data(node* n);

/* Taille (en nombre de blocs) du champs data */
extern size_t nb_blocs_data(node* n);

/* Taille (en nombre de blocs) de l'en-tête */
extern size_t nb_blocs_node();

/* 1 si le noeud a un successeur, 0 sinon */
extern short has_next(node* n);

/*************************************************************************/
#endif
/*************************************************************************/
