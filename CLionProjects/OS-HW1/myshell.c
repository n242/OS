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


/*
        char *cmd = "ls";
        char *arg[3];
        arg[0] = "ls";
        arg[1] = "-la";
        arg[2] = NULL;

        execvp(cmd, arg); //This will run "ls -la" as if it were a command
*/

        char *argv[BUFFER_SIZE];
        *argv = command; //initializing location of argv
        int i=0, j;
        int status;
        char *tmp = strtok(command ," ");//strok returns ptr to first argument in string
        printf("before while\n");

        char str1[] = "/bin/";
        char * new_str ;

        while(tmp!=NULL)
        {
            printf("in while %d\n", i);
            printf ("%s\n",tmp);

            if(i==0)
            {
                if((new_str = malloc(strlen(str1)+1)) != NULL) {
                    new_str[0] = '\0';   // ensures the memory is an empty string
                    printf("test\n");
                    strcat(argv[i], str1); //adds second argument to first
                    printf("%s\n", argv[i]);
                    printf("test2\n");
                }
            }

            argv[i] = tmp;//initializing location of argv[i]

            strcpy(argv[i], tmp);
            printf ("%s\n",argv[i]);
            printf("in while after copy argv %d\n", i);
            tmp = strtok(NULL, " ");
            printf("in while after tmp strtok %d\n", i);
            i+=1;
            printf("in while before round:  %d\n", i);

        }
        printf("after while\n");
        char* first = strtok(command, " ");
        if(first==NULL)
        {
            printf("ERROR: strtok failed\n");
            exit(1);
        }
        printf ("first is: %s\n",first);

        char * new_str2 ;
        if((new_str2 = malloc(strlen(first)+strlen(str1))) != NULL){
            new_str2[0] = '\0';   // ensures the memory is an empty string
            strcat(new_str2,str1); //adds second argument to first
            strcat(new_str2,first);
        } else {
            printf("ERROR: can't add /bin/ failed\n");
        }
        /*
         * if(strcmp(argv[i-1], "&")==0)//run at bg
        {
            printf("run at bg\n");
        }
        else //run at front
        {
         */

            pid_t pid = fork(); //fork a child process
            if(pid<0)
            {
                printf("ERROR: fork failed\n");
                exit(1);
            }
            else if(pid==0)
            {
                printf("Before calling execvp()\n");
                for(;i>=0; i--)
                    printf("argv[%d] is: %s\n",i, argv[i]);
                printf("%s\n", new_str2);
                if(execvp(new_str2, argv) ==-1) //first arg is * second is **
                {
                    printf(("ERROR: execvp failed\n"));
                    exit(1);
                }
            }
            else{
                while (wait(&status) != pid)
                    ;
            }

        }//end while 1



        printf("This line will not be printed if execvp() runs correctly\n");

    /*
     * free(first);
        for(j=0; j<i; j++)
        {
            free(argv[j]);
        }
     */



    return 0;
}
