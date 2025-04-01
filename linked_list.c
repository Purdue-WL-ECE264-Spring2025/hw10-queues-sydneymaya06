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
  //printf("insert at tail\n");
  // printf("val: %d\n", (int)value);
  // printf("address %p\n", list->head);
  if(list->head == NULL)
  {
    // printf("list is NULL\n");
    list->head = new_node(value);
    return;
  }
  struct list_node * p = list->head;
  //printf("%d\n", (int)p->value);
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
  if(list->head == NULL)
  {
    return -1;
  }
  struct list_node * p = list->head;
  struct list_node * q;
  while((p->next != NULL))
  {
    q = p;
    p = p->next;
  }
  q -> next = NULL;
  size_t val = p->value;
  free(p);
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
