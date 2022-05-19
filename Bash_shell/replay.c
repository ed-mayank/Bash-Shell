#include "shell.h"

void replay(){
    signalHandling();
    int wstatus;
    int pid = fork();
    if(pid < 0){
        perror("Error");
        return;
    }
    if(pid==0){
        int i=0,j=0;
        char cmnd[SIZE];
        int interval,period;
        char* token = strtok(laterPart,"-");
        while(token!=NULL){
            if(i==0){
                while(token[j]!=' '){
                    j++;
                }
                strcpy(cmnd,&token[j+1]);
            }
            else if(i==1){
                while(token[j]!=' '){
                    j++;
                }
                interval = atoi(&token[j+1]);
            }
            else if(i==2){
                while(token[j]!=' '){
                    j++;
                }
                period=atoi(&token[j+1]);
            }
            i++;
            j=0;
            token=strtok(NULL,"-");
        }
        while(period >=0){
            if(period >= interval){
                sleep(interval);
                functionCall(cmnd);
            }
            else{
                sleep(period);
                return;
            }
            period = period-interval;
        }
    }
    else{
        fg_process=pid;
        waitpid(pid,&wstatus,WUNTRACED);
    }
}