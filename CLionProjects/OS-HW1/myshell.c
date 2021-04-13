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
        int j;

        char* location = strstr(command, "&");
        if(location!=NULL){
            //printf("location is: %s\n" ,location);
            //printf("in run at bg\n");
            run_at_bg = 1;
            command[strcspn(command, " &")] = 0; //removing final &
           // printf("run at bg is: %d\n", run_at_bg);
        }

       // printf("run at bg is: %d\n", run_at_bg);

        char *argv[BUFFER_SIZE];
        *argv = command; //initializing location of argv
        int i=0;
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


        printf("i is: %d\n", i);
        //for(;i>=0; i--)
         //   printf("argv[%d] is: %s \n",i, argv[i]);
        pid_t pid = fork(); //fork a child process
        if(pid<0){
            printf("ERROR: fork failed\n");
            exit(1);
        }
        else if(pid==0 || run_at_bg==1){
            for(;i>=0; i--)
                printf("argv[%d] is: %s \n",i, argv[i]);
            if(execvp(argv[0], argv) <0) {//first arg is * second is **
                printf(("ERROR: execvp failed\n"));
                }
                exit(1);
            }
        if(run_at_bg==1){
                return 0;
            }
        else{ //waiting while pid>0
            while (wait(&status) != pid)
                ;
                //return status;
        }

    }//end while 1

        //printf("This line will not be printed if execvp() runs correctly or after exit\n");
    return 0;
}
