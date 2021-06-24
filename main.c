/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "tests.h"
#include <stdio.h>
#include <stdlib.h>



/* FONCTION PRINCIPALE ================================================= */

int main(int argc, char* argv[]){


	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("==================================================================================================\n");

	int seq = 3;
	size_t loop = 10000;
	short affiche = 1;
	size_t octets = 100000*sizeof(align_data);
	short compare = 0;

	if (argc>1){
		int a = atoi(argv[1]);
		if (a>0) loop = a;
	}

	printf("\nNombre d'opérations : %ld\n",loop);

	if (argc>2){
		int a = atoi(argv[2]);
		if (a==0 || a==1 || a==2) affiche = a;
	}

	if (affiche==2) printf("Affichage de la liste à chaque opérations.\n");
	else if (affiche==1) printf("Affichage de la liste en fin de test.\n");
	else printf("\nNe pas afficher la liste.\n");

	if (argc>3){
		int a = atoi(argv[3]);
		if (a==0 || a==1 || a==2 ) compare = a;
	}


	if (argc>4){
			int a = atoi(argv[4]);
			if (a > 10*sizeof(align_data) ) octets = a;
	}

	if (compare==2||compare==0){
		printf("\nNombre d'octets à allouer  : %ld\n",octets);
		srandom(seq);
		test(octets,loop,affiche,0);
	}
	if (compare==1 || compare==2){
		printf("\nOpérations sur une liste classique.\n");
		srandom(seq);
		test(octets,loop,affiche,1);
	}

	return 0;
}

/*************************************************************************/
