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
}

struct list {
    node* head;
    //node* tail;
    //TODO: check what other fields to add - mutex?
}
/*
 * void print_node(node* node)
{
  // DO NOT DELETE
  if(node)
  {
    printf("%d ", node->value);
  }
}
 */


list* create_list() //TODO: check if a mutex is necessary here
{
    list *new_list=NULL;
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
    while(list->head && list->head->next)//delete while not null and next for mutex
    {
        pthread_mutex_lock(&list->head->mutex);
        pthread_mutex_lock(&list->head->next->mutex);
        node* delete_node = list->head;
        //while(0){
            pthread_mutex_unlock(&list->head->next->mutex);
        list->head=list->head->next;
        free(delete_node);//TODO: check it's legal
    }
    pthread_mutex_lock(&list->head->mutex); //locking again to free final node
    free(list->head);
    free(list);
}

void insert_value(list* list, int value) {

    node *new_node = NULL;
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
  //save next of prev, delete myself, unlock prev
  if(list->head==NULL){
      return; //didn't find value
  }
  if(list->head->next == NULL ){
      pthread_mutex_lock(&list->head->mutex);
      if(list->head->value==value){
          free(list->head);
          return;
      }
      else{
          pthread_mutex_unlock(&list->head->mutex);
      }
  }
  if(list->head->value == value)
  {
      pthread_mutex_lock(&list->head->mutex);
      node* tmp_node = list->head;
      list->head = list->head->next;
      pthread_mutex_unlock(&list->head->mutex);
      free(tmp_node);
      return;
  }
  else{ //have more than 1 node in list
    node* tmp = list->head;
    while(list->head->next && list->head->next->value!= value)
    {
        pthread_mutex_lock(&list->head->mutex); //locking to get next
        node* curr = list->head;
        list->head = list->head->next;
        pthread_mutex_unlock(&curr->mutex);
    }
   if(list->head->next && list->head->next->value == value){ //found value in list
       pthread_mutex_lock(&list->head->mutex);
       node* next_node = list->head->next->next;
       free(list->head->next);
       list->head->next = next_node;
       pthread_mutex_unlock(&list->head->mutex);
   }
    list->head = tmp; //restoring head ptr
  }
}

void print_list(list* list)
{
    if(list->head){
        node* tmp = list->head;
        while(list->head && list->head->next)
        {
            if(pthread_mutex_lock(&list->head->mutex)!=0){
            perror("mutex_lock");
            exit(2);
        }
        pthread_mutex_lock(&list->head->next->mutex);

        printf("%d ", list->head->value);
        pthread_mutex_unlock(&list->head->next->mutex);
        node* curr = list->head;
        list->head=list->head->next;
            //while(0) {
                pthread_mutex_unlock(&curr->mutex);
            //}
        }
        pthread_mutex_lock(&list->head->mutex);
        printf("%d ", list->head->value);
        pthread_mutex_unlock(&list->head->mutex);

    list->head = tmp;
    }
    printf("\n"); // DO NOT DELETE
    return;
    //while not null and unlocked - lock and print
}

void count_list(list* list, int (*predicate)(int))
{
  int count = 0; // DO NOT DELETE
  node* tmp = list->head; //saving head ptr

  while(list->head && list->head->next)
  {
      //while(1){
      pthread_mutex_lock(&list->head->mutex);
      pthread_mutex_lock(&list->head->next->mutex);
      count++;
      //}
      //while(0){
          pthread_mutex_unlock(&list->head->next->mutex);
      //}

      node* curr = list->head;
      list->head=list->head->next;
      //while(0){
          pthread_mutex_unlock(&curr->mutex);
  //}
  }
    pthread_mutex_lock(&list->head->mutex);
    count++;
    pthread_mutex_unlock(&list->head->mutex);
    list->head = tmp; //restoring head ptr

  printf("%d items were counted\n", count); // DO NOT DELETE
}
