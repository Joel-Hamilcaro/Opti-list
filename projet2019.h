/*************************************************************************/
#ifndef PROJET2019_H
#define PROJET2019_H
/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include "noeud.h"
#include "tranche.h"

/* STRUCTURES ========================================================== */

typedef struct {
	void* memory;
	ptrdiff_t first;
	ptrdiff_t last;
	tranche* libre;
	size_t allocated_blocs; /* nombre de blocs alloués */
	size_t length;
} head;

/* FONCTIONS =========================================================== */

/* 2.2.1 */
extern void* ld_create(size_t nboctets);
/* 2.2.2 */
extern void* ld_first(void* liste);
/* 2.2.3 */
extern void* ld_last(void* liste);
/* 2.2.4 */
extern void* ld_next(void* liste, void* current);
/* 2.2.5 */
extern void* ld_previous(void* liste, void* current);
/* 2.2.6 */
extern void ld_destroy(void* liste);
/* 2.2.7 */
extern size_t ld_get(void* liste, void* current, size_t len , void* val);
/* 2.2.8 */
void* ld_insert_first(void *liste, size_t len, void* p_data);
/* 2.2.9 */
void* ld_insert_last(void* liste, size_t len, void* p_data);
/* 2.2.10 */
void* ld_insert_before(void* liste, void* n, size_t len, void* p_data);
/* 2.2.11 */
void* ld_insert_after(void* liste, void* n, size_t len, void* p_data);
/* 2.3 */
void* ld_delete_node(void* liste, void* n);
/* 2.3.1 */
size_t ld_total_free_memory(void *liste);
/* 2.3.2 */
size_t ld_total_useful_memory(void * liste);
/* 2.3.3 */
void* ld_add_memory(void* liste, size_t nboctets);
/* 2.3.4 */
void *ld_compactify(void *liste);

/*************************************************************************/
#endif
/*************************************************************************/
