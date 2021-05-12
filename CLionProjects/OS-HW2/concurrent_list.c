#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "concurrent_list.h"

struct node {
  int value;
  node* next;
  pthread_mutex_t mutex ;
  //TODO: QUEUE? check if necessary - if starvation is checked
};

struct list {
    node* head;
    //node* tail;
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

list* create_list() //TODO: check if a mutex is necessary here
{
    list* new_list=NULL;
    if (!(new_list = (list*) malloc(sizeof(list))))
    {
        printf("Memory overflow in create_list.\n");
        exit(100);
    }
    new_list->head = NULL;
   // new_list->tail = new_list->head;
  return new_list;
}

void delete_list(list* list)
{
    if(!list){
        return;
    }
    if(list->head){


    pthread_mutex_lock(&list->head->mutex);
    while(list->head->next)//delete while not null and next for mutex
    {
        pthread_mutex_lock(&list->head->next->mutex);
        node* delete_node = list->head;
        //while(0){
        pthread_mutex_unlock(&list->head->next->mutex);
        list->head=list->head->next;
        pthread_mutex_unlock(&list->head->mutex);
        pthread_mutex_destroy(&list->head->mutex);
        free(delete_node);
    }

    if(list->head->next){ //TODO: fix mutex here
        pthread_mutex_unlock(&list->head->next->mutex);
        pthread_mutex_destroy(&list->head->next->mutex);
        free(list->head->next);
        }
    pthread_mutex_unlock(&list->head->mutex);
    pthread_mutex_destroy(&list->head->mutex);
    }
    free(list->head);
    free(list);
}

void insert_value(list* list, int value) {
    node* new_node = NULL;
    if (!(new_node = (node *) malloc(sizeof(node)))) {
        printf("Memory overflow in insert.\n");
        exit(100);
    }
    new_node->value = value;
    pthread_mutex_init(&(new_node->mutex), NULL); //initializing mutex here so can lock elsewhere
    if (list->head==NULL) { //nothing to lock
        new_node->next = NULL;
        list->head = new_node;
        return;
    }
    if (list->head->value > value) {//insert node at top
        pthread_mutex_lock(&list->head->mutex);
        node *next_node = list->head;
        pthread_mutex_unlock(&list->head->mutex);
        list->head = new_node;
        new_node->next = next_node;
    }
    else{ //need to insert value to mid-list
        node* tmp = list->head; // saving list ptr before while
        while (list->head->next && list->head->next->value < value)
        {
            pthread_mutex_lock(&list->head->mutex); //locking to get next
            node* curr = list->head;
            list->head = list->head->next;
            pthread_mutex_unlock(&curr->mutex);
        }
        if (list->head->value < value) //insert node after head
        {
            pthread_mutex_lock(&list->head->mutex);
            node *next_node = list->head->next;
            list->head->next = new_node;
            pthread_mutex_unlock(&list->head->mutex);//finished dealing with node so can unlock
            new_node->next = next_node;
        }
        list->head = tmp; //restoring list ptr
    }
    //create new node in correct place, lock prev, create current
    // mutex unlocked
}
void remove_value(list* list, int value)
{
  if(list->head==NULL){
      return; //value not in empty list
  }
  pthread_mutex_lock(&list->head->mutex);
  if(list->head->value==value){
      if(list->head->next == NULL ){
          pthread_mutex_unlock(&list->head->mutex);
          free(list->head);
          return;
      }
      else{
          node* tmp_node = list->head;
          list->head = list->head->next;
          pthread_mutex_unlock(&list->head->mutex);
          free(tmp_node);
          return;
      }
  }
  if(list->head->next == NULL)
  {
      pthread_mutex_unlock(&list->head->mutex);
      return; //didn't find value
  }
  else{ //have more than 1 node in list
      pthread_mutex_lock(&list->head->next->mutex); //locking to get next, head is still locked
    node* tmp = list->head;
    while(list->head->next && list->head->next->value < value)
    {
        node* curr = list->head;
        list->head = list->head->next;
        pthread_mutex_lock(&list->head->mutex); //locked next
        pthread_mutex_unlock(&curr->mutex); //TODO: everywhere lock next then unlock current
    }
   if(list->head->next && list->head->next->value == value){ //found value in list
       node* next_node = list->head->next->next;
       pthread_mutex_unlock(&list->head->next->mutex);
       free(list->head->next);
       pthread_mutex_unlock(&list->head->mutex);
       list->head->next = next_node;
   }
    list->head = tmp; //restoring head ptr
    pthread_mutex_unlock(&list->head->mutex);
  }
}

void print_list(list* list)
{
    if(list && list->head){
        node* tmp = list->head;
        pthread_mutex_lock(&list->head->mutex);
        while(list->head && list->head->next) //while not null and unlocked - lock and print
        {
            pthread_mutex_lock(&list->head->next->mutex);
            printf("%d ", list->head->value);
            node* curr = list->head;
            list->head=list->head->next;
            pthread_mutex_unlock(&curr->mutex);
        }
        printf("%d ", list->head->value);
        list->head = tmp;
        pthread_mutex_unlock(&list->head->mutex);
    }
    printf("\n"); // DO NOT DELETE
    return;
}

void count_list(list* list, int (*predicate)(int))
{
  int count = 0; // DO NOT DELETE
  if(list == NULL){
      printf("%d items were counted\n", count); // DO NOT DELETE
      return;
  }
  pthread_mutex_lock(&list->head->mutex);
  node* tmp = list->head; //saving head ptr
  while(list->head && list->head->next)
  {
      pthread_mutex_lock(&list->head->next->mutex);
      count += predicate(list->head->value); //predicate returns 1 if we get value bigger than inserted
      node* curr = list->head;
      list->head=list->head->next;
      pthread_mutex_unlock(&curr->next->mutex);
  }
  if(list->head){
      count += predicate(list->head->value); //counting current
      list->head = tmp; //restoring head ptr
      pthread_mutex_unlock(&list->head->mutex);
  }
  printf("%d items were counted\n", count); // DO NOT DELETE
}
