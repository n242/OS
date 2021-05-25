#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "concurrent_list.h"

struct node {
  int value;
  node* next;
  pthread_mutex_t mutex ;
};

struct list {
    node* head;
    //node* tail;
    pthread_mutex_t mutex ;
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
        printf("Memory overflow in create_list.\n");
        exit(100);
    }
    new_list->head = NULL;
    pthread_mutex_init(&(new_list->mutex), NULL); //initializing mutex here so can lock elsewhere
   // new_list->tail = new_list->head;
  return new_list;
}

void delete_list(list* list)
{
    if(!list){
        return; //list is null, nothing to delete
    }
    pthread_mutex_lock(&list->mutex);
    if(list->head){
        pthread_mutex_lock(&list->head->mutex);
        while(list->head->next)//delete while not null and next for mutex
        {
            pthread_mutex_lock(&list->head->next->mutex);
            node* delete_node = list->head;
            //while(0){
            list->head=list->head->next;
            pthread_mutex_unlock(&list->head->mutex);
            //pthread_mutex_destroy(&list->head->mutex);
            free(delete_node);
        }
        pthread_mutex_unlock(&list->head->mutex);
        //pthread_mutex_destroy(&list->head->mutex);
        free(list->head);
    }

    pthread_mutex_unlock(&list->mutex);
   // pthread_mutex_destroy(&list->mutex);
    free(list);
}

void insert_value(list* list, int value) {
    node* new_node = NULL;
    if (!(new_node = (node *) malloc(sizeof(node)))) {
        printf("Memory overflow in insert.\n");
        exit(100);
    }
    new_node->value = value;
    new_node->next = NULL;
    pthread_mutex_init(&(new_node->mutex), NULL); //initializing mutex here so can lock elsewhere
    if (list->head==NULL) { //nothing to lock
        new_node->next = NULL;
        list->head = new_node;
        return;
    }
    pthread_mutex_lock(&list->head->mutex);
    if (list->head->value > value) {//insert node at top
        node *next_node = list->head;
        pthread_mutex_unlock(&list->head->mutex);
        list->head = new_node;
        new_node->next = next_node;
    }
    else{ //need to insert value to mid-list
        node* tmp = list->head; // saving list ptr before while
        while (list->head->next && list->head->next->value < value)
        {
            pthread_mutex_lock(&list->head->next->mutex); //locking to get next
            node* curr = list->head;
            list->head = list->head->next;
            pthread_mutex_unlock(&curr->mutex);
        }
        if (list->head->value < value) //insert node after head
        {
            node *next_node = list->head->next;
            list->head->next = new_node;
            pthread_mutex_unlock(&list->head->mutex);//finished dealing with node so can unlock
            new_node->next = next_node;
        }
        list->head = tmp; //restoring list ptr
    } //had to unlock head anyway beforehand
}


/*
 *  while (list->head->next && list->head->next->value < value)
        {
            pthread_mutex_lock(&list->head->next->mutex); //locking to get next
            node* curr = list->head;
            list->head = list->head->next;
            pthread_mutex_unlock(&curr->mutex);
        }
        if (list->head->value < value) //insert node after head
        {
            node *next_node = list->head->next;
            list->head->next = new_node;
            pthread_mutex_unlock(&list->head->mutex);//finished dealing with node so can unlock
            new_node->next = next_node;
        }
        list->head = tmp; //restoring list ptr
    } //had to unlock head anyway beforehand
}




 else{ //need to insert value to mid-list
        node* tmp = list->head; // saving list ptr before while
        int flag = 0;
        if(list->head->next){
            pthread_mutex_lock(&list->head->next->mutex);
        }
        while (list->head->next && list->head->next->value < value)
        {
            if(flag==1){
                pthread_mutex_lock(&list->head->next->mutex); }//locking to get next
            node* curr = list->head;
            list->head = list->head->next;
            pthread_mutex_unlock(&curr->mutex);
            flag = 1;
        }
        if (list->head->value < value) //insert node after head
        {
            node *next_node = list->head->next;
            list->head->next = new_node;
            pthread_mutex_unlock(&list->head->mutex);//finished dealing with node so can unlock
            new_node->next = next_node;
        }
        list->head = tmp; //restoring list ptr
    } //had to unlock head anyway beforehand
}
 */
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
      else{ //found value in head, next isn't null
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
        node* tmp = list->head;
        while(list->head->next && list->head->next->value < value)
        {
            pthread_mutex_lock(&list->head->next->mutex); //locked next while isn't already locked
            node* curr = list->head;
            list->head = list->head->next;
            pthread_mutex_unlock(&curr->mutex);
        }
       if(list->head->next && list->head->next->value == value){ //found value in list
           node* next_node = list->head->next->next;
           pthread_mutex_unlock(&list->head->next->mutex);
           free(list->head->next);
           pthread_mutex_unlock(&list->head->mutex);
           list->head->next = next_node;
       }

   else{ //didn't find value, unlocking next
       list->head = tmp; //restoring head ptr
       pthread_mutex_unlock(&list->head->next->mutex);
       pthread_mutex_unlock(&list->head->mutex);
       return;
   }
   list->head = tmp; //restoring head ptr
  }
    pthread_mutex_unlock(&list->head->mutex);
}

void print_list(list* list)
{
    if(list && list->head){
        pthread_mutex_lock(&list->head->mutex);
        node* tmp = list->head;
        while(list->head->next) //while not null and unlocked - lock and print
        {
            pthread_mutex_lock(&list->head->next->mutex);
            printf("%d ", list->head->value);
            node* curr = list->head;
            list->head=list->head->next;
            pthread_mutex_unlock(&curr->mutex);
        }
        printf("%d ", list->head->value);
        pthread_mutex_unlock(&list->head->mutex);//unlocking current
        list->head = tmp;
        pthread_mutex_unlock(&list->head->mutex); //unlocking head TODO: check if necessary
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
