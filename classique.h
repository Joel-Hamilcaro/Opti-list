/*************************************************************************/
#ifndef CLASSIQUE_H
#define CLASSIQUE_H
/*************************************************************************/

typedef struct cld_node {
  void* data;
  size_t nb_blocs_data;
  struct cld_node* previous;
  struct cld_node* next;
} cld_node;

typedef struct{
  cld_node* first;
  cld_node* last;
  size_t length;
} cld_head;

/* FONCTIONS =========================================================== */

cld_head* cld_create(cld_node* first, cld_node* last);

void cld_destroy(cld_head* target_list);

void* cld_insert_first(cld_head* target_list, size_t len, void* p_data);

void* cld_insert_last(cld_head* target_list, size_t len, void* p_data);

void* cld_insert_before(cld_head* target_list, cld_node* n, size_t len, void* p_data);

void* cld_insert_after(cld_head* target_list, cld_node* n, size_t len, void* p_data);

void* cld_delete_node(cld_head* target_list, cld_node* n);

/*************************************************************************/
#endif
/*************************************************************************/
