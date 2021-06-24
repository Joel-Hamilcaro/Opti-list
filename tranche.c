/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "tranche.h"
#include <stdio.h>
#include <stdlib.h>


/* FONCTIONS =========================================================== */

/* initialisation de toutes les cases d'un tableau de tranche t */
void init_tranches(tranche* t){
	for (int i=0; i<NTRANCHES ; i++){
		t[i].decalage = ID_VIDE;
		t[i].nb_blocs = 0;
	}
}

int nb_tranches(tranche* t){
	for (int i=0; i<NTRANCHES ; i++){
		if (t[i].decalage==ID_VIDE) return i;
	}
	return 1;
}

/* Décale tous les éléments après index d'une case */
/* Vers la droite ecrase la derniere case */
/* Vers la gauche ecrase la case index */
static void decaler(tranche *t, size_t index, short vers_la_droite){
	if (vers_la_droite){
		tranche tmp1 = t[index];
		tranche tmp2 = t[index+1];
		for (int i=index+1; i<NTRANCHES-2 && t[i-1].decalage>ID_VIDE ; i+=2){
			t[i] = tmp1;
			tmp1 = t[i+1];
			t[i+1] = tmp2;
			tmp2 = t[i+2];
		}
	}
	else {
		for (int i=index; i<NTRANCHES-1 && t[i].decalage>ID_VIDE; i++){
			t[i]=t[i+1];
		}
	}
}

/* Utilisation d'une tranche libre pouvant stocker "len" blocs. Le tableau
  est mis à jour et on renvoie la position (décalage) de cette tranche. */
ptrdiff_t use_tranche(tranche* t, size_t len){
	for (int i=0; t[i].decalage > ID_VIDE && i<NTRANCHES ; i++){
		if (t[i].nb_blocs >= len ){
			ptrdiff_t decalage = t[i].decalage ;
			t[i].decalage += len;
			t[i].nb_blocs -= len;
			if (t[i].nb_blocs==0) decaler(t,i,0);
			return decalage;
		}
	}
	return ID_VIDE;
}


/* Mise à jour des tranches après libération de "nb_blocs" blocs, à la
   position "decalage". */
void add_tranche(tranche* t, size_t nb_blocs, ptrdiff_t decalage){
	int i = 0;
	while(i<NTRANCHES-1 && t[i].decalage>ID_VIDE && t[i].decalage<decalage) i++;
	int b = 0;
	/* Fusion à gauche */
	if (i>0 && (t[i-1].decalage+t[i-1].nb_blocs)==decalage ){
		t[i-1].nb_blocs += nb_blocs;
		b=1;
	}
	if (i<NTRANCHES-1 && (decalage+nb_blocs==t[i].decalage) ){
		if (b){ /* fusion à gauche et à droite */
			t[i-1].nb_blocs += t[i].nb_blocs;
			decaler(t,i,0); /* on efface une case */
			return;
		}
		else { /* fusion à droite mais pas à gauche */
			t[i].decalage = decalage;
			t[i].nb_blocs += nb_blocs;
			return;
		}
	}
	if (b) return; /* fusion à gauche mais pas à droite */

	/* Aucune fusion */
	decaler(t,i,1); /* on decale les case à droite */
	t[i].decalage = decalage;
	t[i].nb_blocs = nb_blocs;
}

/*************************************************************************/
