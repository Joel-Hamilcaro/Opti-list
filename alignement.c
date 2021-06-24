/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "alignement.h"

/* FONCTIONS =========================================================== */

/* Nombre de blocs suffisants pour stocker o octets */
size_t nb_blocs(size_t o){
  size_t size = sizeof(align_data);
	return o%size==0 ? o/size : o/size+1 ;
}

/*************************************************************************/
