#include "shell.h"

void bg(){
    int i=0;
    char* args[SIZE];
    args[0]=strtok(laterPart," ");
    while(args[i]!=NULL){
        i++;
        args[i]=strtok(NULL," ");
    }
    if(i!=1){
        printf("Error: Invalid input\n");
        return;
    }
    int prNum = atoi(args[0]);
    if(prNum==0){
        printf("Error: Invalid input\n");
        return;
    }
    if(prNum>prCount){
        printf("Process does not exist\n");
        return;
    }
    kill(Pr[prNum].pId,SIGCONT);
}