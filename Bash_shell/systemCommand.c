#include "shell.h"

void systemCommand(char *commands){
    int b_flag=0;
    char* args[SIZE];
    char* tk;
    for(int i=0;i<SIZE;i++){
        args[i]="";
    }
    int i=0;
    tk = strtok(commands," ");
    while(tk!=NULL){
        if(strcmp(tk,"&")==0){
            b_flag=1;
        }
        else{
            args[i]=tk;
            i++;
        }
        tk=strtok(NULL," ");
    }
    args[i]=NULL;
    if(b_flag){
        bgProcess(args);
    }else{
        fgProcess(args);
    }
}