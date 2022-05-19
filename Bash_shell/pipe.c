#include "shell.h"

void virtualFile(char *text, int i, int totalPipes)
{
    if (i%2==1){ 
        if (pipe(fd1) == -1){
            perror("pipe1 creation error");
            return;
        }
    }else{
        if (pipe(fd2) == -1){
            perror("pipe2 creation error");
            return;
        }
    }
    int pid = fork();

    if (pid == -1){
        perror("Process creation error in pipline");
        return;
    }
    if (pid==0){
        if (i == 0){
            dup2(fd2[1], 1);
        }
        else if (totalPipes == i){
            if (totalPipes & 1){
                dup2(fd2[0], 0);
            }
            else{
                dup2(fd1[0], 0);
            }
        }
        else{
            if (i & 1){
                dup2(fd2[0], 0);
                dup2(fd1[1], 1);
            }
            else{
                dup2(fd1[0], 0);
                dup2(fd2[1], 1);
            }
        }
        functionCall(text);

        exit(0);
    }

    wait(NULL); //wait till child terminate

    if (i == 0)
    {
        close(fd2[1]);
    }
    else if (i == totalPipes){
        if (totalPipes & 1) {
            close(fd2[0]);
        }else {
            close(fd1[0]);
        }
    }
    else {
        if (i & 1){
            close(fd2[0]);
            close(fd1[1]);
        }else{
            close(fd1[0]);
            close(fd2[1]);
        }
    }
}

void pipeline(char* commands){
    char* args[SIZE];
    int i=0;
    int num = pipe_flag;
    args[0]=strtok(commands,"|");
    while(args[i]!=NULL){
        args[i]=handleSpace(args[i]);
        virtualFile(args[i],i,num);
        i++;
        args[i]=strtok(NULL,"|");
    }
}