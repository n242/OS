#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100


int main(void)
{
    close(2);
    dup(1);
    char command[BUFFER_SIZE];

    while (1)
    {
        fprintf(stdout, "my-shell> ");
        memset(command, 0, BUFFER_SIZE);
        fgets(command, BUFFER_SIZE, stdin);
        if(strncmp(command, "exit", 4) == 0)
        {
            break;
        }
        //my code below

        //strok returns ptr to first argument in string
        char* first = strtok(command, " ");
        if(first==NULL)
        {
            printf("ERROR: strtok failed\n");
            exit(1);
        }
        char *argv[BUFFER_SIZE];
        char *tmp = strtok(command ," ");
        int i=0, j;
        while(tmp!=NULL)
        {
            tmp = strtok(NULL, " ");
            argv[i] = strtok(NULL, " ");
            i++;
        }
        //strcpy(first, cmd);//copies cmd to first
        int status;
        pid_t pid = fork();
        if(pid<0)
        {
            printf("ERROR: fork failed\n");
            exit(1);
        }
        else if(pid==0)
        {
            printf("Before calling execvp()\n");
            if(execvp(first, argv) <0) //first arg is * second is **
            {
                printf(("ERROR: execvp failed\n"));
            }
        }
        else while(wait(&status)!=pid)
            ;


        printf("This line will not be printed if execvp() runs correctly\n");

        free(first);
        for(j=0; j<i; j++)
        {
            free(argv[j]);
        }
    }

    return 0;
}
