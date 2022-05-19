#include "shell.h"

void fgProcess(char* args[]){
    pid_t pid;
    int wstatus;
    pid = fork();
    if(pid == -1){
        perror("Error");
        exit(0);
    }
    if(pid == 0) //child process
    {
        int status = execvp(args[0],args);
        if(status == -1){
            perror("Error");
            exit(0);
        }
    }
    else{
        fg_process=pid;
        strcpy(fg_processName,args[0]);
        waitpid(pid,&wstatus,WUNTRACED);   //wait till child finish its process
    }
    return;
}