/*************************************************************************/
#ifndef TRANCHE_H
#define TRANCHE_H
/*************************************************************************/

#include <stddef.h>

/* CONSTANTES ========================================================== */

#define NTRANCHES 1024
#define ID_VIDE -1

/* STRUCTURES ========================================================== */

typedef struct {
	ptrdiff_t decalage;
	size_t nb_blocs;
} tranche;

/* FONCTIONS =========================================================== */

/* initialisation de toutes les cases d'un tableau de tranche t */
extern void init_tranches(tranche* t);

/* Renvoie le nombre de tranches */
extern int nb_tranches(tranche* t);

/* Utilisation d'une tranche libre pouvant stocker "len" blocs. Le tableau
  est mis à jour et on renvoie la position (décalage) de cette tranche. */
extern ptrdiff_t use_tranche(tranche* t, size_t len);

/* Mise à jour des tranches après libération de "nb_blocs" blocs, à la
   position "decalage". */
extern void add_tranche(tranche* t, size_t nb_blocs, ptrdiff_t decalage);

/*************************************************************************/
#endif
/*************************************************************************/
