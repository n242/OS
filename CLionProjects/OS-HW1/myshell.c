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

        command[strcspn(command, "\n")] = 0; //removing /n from final string
        int run_at_bg = 0;//adding flag to check if to run process at bg

        char* location = strstr(command, "&"); //checking if to run at bg
        if(location!=NULL){
            run_at_bg = 1;
            command[strcspn(command, " &")] = 0; //removing final &
        }

        char *argv[BUFFER_SIZE];
        *argv = command; //initializing location of argv
        int i=0;//number of arguments
        int status;
        char *tmp = strtok(command ," ");//strok returns ptr to first argument in string

        if(tmp==NULL)
            exit(1);
        while(tmp!=NULL){
            argv[i] = tmp;//initializing location of argv[i]
            strcpy(argv[i], tmp);
            tmp = strtok(NULL, " "); //proceeding tmp to next word
            i+=1;
        }
        argv[i] = NULL;
        int len =i;

        pid_t pid = fork(); //fork a child process
        //if(pid<0){
            //printf("ERROR: fork failed\n");
        //    exit(1);
        //}
        if(pid==0 || run_at_bg==1){
            execvp(argv[0], argv);//first arg is * second is **
            //if(execvp(argv[0], argv) <0) {
             //   printf(("ERROR: execvp failed\n"));
            //    }
                exit(1);
            }
        if(run_at_bg==1){
                return 0;
            }
        else{ //waiting while pid>0
            while (wait(&status) != pid)
                ;
        }
    }//end while 1

    return 0;
}
