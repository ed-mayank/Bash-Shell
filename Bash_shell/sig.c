#include "shell.h"

void sig(){
    int i = atoi(strtok(laterPart," "));
    int sigNum = atoi(strtok(NULL," "));
    if(i==0 || sigNum ==0){
        printf("Error: Invalid input\n");
        return;
    }
    if(prCount < i){
        printf("Error: Process number %d does not exist",i);
        return;
    }
    kill(Pr[i].pId,sigNum);
}