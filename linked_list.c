#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) 
{ 
  struct list_node * nd = malloc(sizeof(struct list_node));
  nd -> value = value;
  nd -> next = NULL;
  return nd; 
}

void insert_at_head(struct linked_list *list, size_t value)
{
  struct list_node * ptr = new_node(value);
  ptr -> next = list->head;
  list->head = ptr;
}

void insert_at_tail(struct linked_list *list, size_t value)
{
  if(list->head == NULL)
  {
    list->head = new_node(value);
    return;
  }
  struct list_node * p = list->head;
  while((p->next != NULL))
  {
    p = p->next;
  }
  p -> next = new_node(value);
  return;
}

size_t remove_from_head(struct linked_list *list) 
{ 
  if(list->head == NULL)
  {
    return -1;
  }
  struct list_node * p = list->head;
  size_t val = p->value;
  list->head = list->head->next;
  free(p);
  
  return val; 
}

size_t remove_from_tail(struct linked_list *list)
{ 
  struct list_node * q = list->head;
  size_t val;
  if(q == NULL)
  {
    return -1;
  }
  if(q -> next == NULL)
  {
    val = q->value;
    list->head = list->head->next;
    free(q);
    return val; 
  }
  struct list_node * p = list->head;
  while((q->next != NULL))
  {
    p = q;
    q = q->next;
  }
  val = p->value;
  free(q);
  p-> next = NULL;
  return val; 
}

void free_list(struct linked_list list) 
{
  while(list.head != NULL)
  {
    struct list_node * p = list.head->next;
    free(list.head);
    list.head = p;
  }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
