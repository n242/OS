//#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "concurrent_list.h"

struct node {
  int value;
  node* next;
  mutex_t m;
  //QUEUE? check if necessary
};

struct list {
    node* head;
    node* tail;
    //TODO: check what other fields to add - mutex?
};

void print_node(node* node)
{
  // DO NOT DELETE
  if(node)
  {
    printf("%d ", node->value);
  }
}

list* create_list()
{
    list* new_list=NULL;

    if (!(new_list = (list*) malloc(sizeof(list))))
    {
        printf("Memory overflow in insert.\n");
        exit(100);
    }
    new_list->head = NULL;
    new_list->tail = new_list->head;
  //TODO: check type - unlock
  return new_list;//
}

void delete_list(list* list)
{
    while(list->head!=NULL)//delete while not null
    {
        node* delete_node = list->head;
        list->head = list->head->next;
        free(delete_node);
    }
    free(list);
  //TODO: check if needs to wait while unlocked
}

void insert_value(list* list, int value) {

    node *new_node = NULL;
    if (!(new_node = (node *) malloc(sizeof(node)))) {
        printf("Memory overflow in insert.\n");
        exit(100);
    }
    new_node->value = value;
    if (list->head == NULL) {
        new_node->next = NULL;
        list->head = new_node;
        return;
    }
    if (list->head->value > value) {//insert node at top
        node *next_node = list->head;
        list->head = new_node;
        new_node->next = next_node;
    }
    else{
        node* tmp = list->head; // saving list pre before while
        while (list->head->next != NULL&& list->head->next->value < value)//insert node
        {
            list->head = list->head->next;
        }
        if (list->head->value < value) //insert node at top
        {
            node *next_node = list->head->next;
            list->head->next = new_node;
            new_node->next = next_node;
        }


        list->head = tmp;
    }
    //create new node in correct place, lock prev, create current
    // mutex unlocked
}
void remove_value(list* list, int value)
{
  //save next of prev, delete myself, unlock prev
  if(list->head==NULL){
      return; //didn't find value
  }
  if(list->head->next == NULL ){
      if(list->head->value==value){
          free(list->head);
          return;
      }
  }
  if(list->head->value == value)
  {
      mutex_lock(&list->head->m);
        node* tmp_node = list->head;
        list->head = list->head->next;
        free(tmp_node);
      mutex_unlock(&list->head->m);
        return;
  }
  else{
    node* tmp = list->head;
    while(list->head->next->value!= value)
    {
        list->head= list->head->next;
        //remove_value(list, value); //recursive call
    }
   // current value is one to remove
   node* next_node = list->head->next->next; //list->next is node need to remove
   free(list->head->next);
   list->head->next = next_node;
    list->head = tmp;
  }
}

void print_list(list* list)
{
    if(list!=NULL){
    node* tmp = list->head;
    while(list->head!=NULL)
  {
      printf("%d", list->head->value);
      printf("\n"); // DO NOT DELETE
      list->head = list->head->next;
      //print_list(list->head->next)
  }
  list->head = tmp;
    }
    return;
    //while not null and unlocked - lock and print
}

void count_list(list* list, int (*predicate)(int))
{
  int count = 0; // DO NOT DELETE
  node* tmp = list->head; //saving head ptr
  while(list->head)
  {
      count++;
      list->head=list->head->next;
  }
    list->head = tmp; //restoring head ptr
  printf("%d items were counted\n", count); // DO NOT DELETE
}
