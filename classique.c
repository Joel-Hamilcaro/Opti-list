/*************************************************************************/

/* INCLUSIONS ========================================================== */

#include <stdlib.h>
#include "alignement.h"
#include <stdio.h>
#include <string.h>
#include "classique.h"

/* FONCTIONS =========================================================== */

/* Création d'un noeud */
static cld_node* cld_create_node(void* p_data, size_t len, cld_node* p, cld_node* ne){
  cld_node* n = malloc(sizeof(cld_node));
  void* data = malloc(len);
  if (n==NULL || data==NULL) return NULL;
  n->data = data;
  n->nb_blocs_data = nb_blocs(len);
  n->previous = p;
  if (p!=NULL){
    p->next = n;
  }
  n->next = ne;
  if (ne!=NULL){
    ne->previous = n;
  }
  memmove(data,p_data,len);
  return n;
}

/* Création d'une liste */
cld_head* cld_create(cld_node* first, cld_node* last){
  cld_head* l = malloc(sizeof(cld_head));
  if (l==NULL) return NULL;
  l->first = first;
  l->last = last;
  l->length = 0;
  return l;
}

/* Destruction de la liste */
void cld_destroy(cld_head* target_list){
  if (target_list==NULL) return;
  for (cld_node* i=target_list->last; i!=NULL; i=i->previous){
    if (i->next!=NULL){
      free(i->next->data);
      i->next->data=NULL;
      free(i->next);
      i->next = NULL;
    }
  }
  if (target_list->first!=NULL && target_list->first->data!=NULL) free(target_list->first->data);
  if (target_list->first!=NULL) free(target_list->first);
  target_list->first = NULL;
  free(target_list);
  target_list = NULL;
}


/* Ajout en première position */
void* cld_insert_first(cld_head* target_list, size_t len, void* p_data){
  if (target_list==NULL || p_data==NULL) return NULL;
  cld_node* n = cld_create_node(p_data,len,NULL,NULL);
  if (n==NULL) return NULL;
  if (target_list->first==NULL){
    target_list->first = n;
    target_list->last = n;
    (target_list->length)++;
    return n;
  }
  n->next = target_list->first;
  target_list->first->previous = n;
  target_list->first = n;
  (target_list->length)++;
  return n;
}

/* Ajout en dernière position */
void* cld_insert_last(cld_head* target_list, size_t len, void* p_data){
  if (target_list==NULL || p_data==NULL) return NULL;
  cld_node* n = cld_create_node(p_data,len,NULL,NULL);
  if (n==NULL) return NULL;
  if (target_list->first==NULL){
    target_list->first = n;
    target_list->last = n;
    target_list->length++;
    return target_list;
  }
  n->previous = target_list->last;
  target_list->last->next = n;
  target_list->last = n;
  target_list->length++;
  return target_list;
}


/* Suppression du first */
static void pop_first(cld_head* target_list){
  if (target_list==NULL) return;
  if (target_list->first==NULL) return;
  if (target_list->first->next!=NULL){ // au moins 2 éléments
    target_list->first = target_list->first->next;
    free(target_list->first->previous->data);
    free(target_list->first->previous);
    target_list->first->previous = NULL;
    target_list->length--;
  }
  else{
    free(target_list->first->data);
    free(target_list->first);
    target_list->first = NULL;
    target_list->last = NULL;
    target_list->length--;
  }
}

/* Suppression du last */
static void pop_last(cld_head* target_list){
  if (target_list==NULL) return;
  if (target_list->first==NULL) return;
  if (target_list->last->previous!=NULL){ // au moins 2 éléments
    target_list->last = target_list->last->previous;
    free(target_list->last->next->data);
    free(target_list->last->next);
    target_list->last->next = NULL;
    target_list->length--;
  }
  else{
    free(target_list->first->data);
    free(target_list->first);
    target_list->first = NULL;
    target_list->last = NULL;
    target_list->length--;
  }
}

/* Ajout d'un noeud à la position index et de valeur value */
void* cld_insert_before(cld_head* target_list, cld_node* n, size_t len, void* p_data){
  if (target_list==NULL || n==NULL || p_data==NULL) return NULL;
  if (n->previous==NULL) return cld_insert_first(target_list,len,p_data);
  cld_node* n2 = cld_create_node(p_data,len,n->previous,n);
  target_list->length++;
  return n2;
}

void* cld_insert_after(cld_head* target_list, cld_node* n, size_t len, void* p_data){
  if (target_list==NULL || n==NULL || p_data==NULL) return NULL;
  if (n->next==NULL) return cld_insert_last(target_list,len,p_data);
  cld_node* n2 = cld_create_node(p_data,len,n,n->next);
  target_list->length++;
  return n2;
}

/* Suppression du noeud à la position index */
void* cld_delete_node(cld_head* target_list, cld_node* n){
  if (target_list==NULL || n==NULL) return 0;
  if (n->previous==NULL){
    pop_first(target_list);
    return target_list;
  }
  if (n->next==NULL){
    pop_last(target_list);
    return target_list;
  }
  (n->next)->previous = n->previous;
  (n->previous)->next = n->next;
  free(n->data);
  free(n);
  n=NULL;
  target_list->length--;
  return target_list;
}
