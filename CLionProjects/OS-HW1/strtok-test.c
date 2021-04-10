#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int i=0,j=0;
   char input[] = "this is a test";
   char * first;
   char** list;
   char* part;
   list = malloc(100*sizeof(char*));
   part = strtok(input," ");
   first = (char*)strdup(part);
   while(part!=NULL){
   /*printf("test %d",i);*/
   list[i] = (char*)strdup(part);
   printf("%s ",list[i]);
   i++;
   part = strtok(NULL," ");
   }


   return 0;
}
