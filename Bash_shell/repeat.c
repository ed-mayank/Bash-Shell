#include "shell.h"

void repeat(){
    signalHandling();
    int wstatus;
    int pid=fork();
    if(pid < 0){
        perror("Error in Repeat function");
        return;
    }
    if(pid==0){
        char* tk;
        char temp[SIZE];
        strcpy(temp,laterPart);
        tk = strtok(temp," ");
        int iter = atoi(tk);
        while(iter--){
            functionCall(&temp[strlen(tk)+1]);
        }
    }else{
        fg_process=pid;
        waitpid(pid,&wstatus,WUNTRACED);
    }
}