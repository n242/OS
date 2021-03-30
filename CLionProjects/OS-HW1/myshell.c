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

        char* tmpPtr = strtok(command, " ");
        if(tmpPtr==NULL)
        {
            printf("ERROR: strtok failed\n");
            exit(1);
        }
        printf("Before calling execvp()\n");
        if(execvp(tmpPtr, command) <0)
        {
            printf(("ERROR: execvp failed\n"));
        }

        printf("This line will not be printed if execvp() runs correctly\n");

        free(tmpPtr);



    }

    return 0;
}
