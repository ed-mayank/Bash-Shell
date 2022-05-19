#include "shell.h"

void fg(){
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    
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
    int fgid = Pr[prNum].pId;
    for(int j=prNum;j<=prCount;j++){
        strcpy(Pr[j].pName,Pr[j+1].pName);
        Pr[j].pId = Pr[j+1].pId;
    }
    prCount--;
    int status;
    fg_process = fgid;
    tcsetpgrp(0, fgid);
    kill(fgid , SIGCONT);
    waitpid(fgid , &status, WUNTRACED);
    tcsetpgrp(0, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}