#include "shell.h"

void jobs(){
    int s_flag=0, r_flag=0;
    if(strstr(laterPart,"-s")) s_flag=1;
    if(strstr(laterPart,"-r")) r_flag=1;
    FILE* f;
    char fpath[SIZE], FR[SIZE], status[SIZE];
    char* tk;
    char* tmp;
    printf("prCount: %d\n",prCount);
    for(int i=1;i<=prCount;i++){
        sprintf(fpath,"/proc/%d/status",Pr[i].pId);
        f = fopen(fpath,"r");
        if(f==NULL){
            printf("NO process with pid=%d exist\n",Pr[i].pId);
            return;
        }
        while(fgets(FR,SIZE,f) != NULL){
            tk=strtok(FR,":\t");
            if(!strcmp(tk,"State")){
                tk = strtok(NULL,":\t");
                tmp = strtok(tk," ");
                if(!strcmp(tmp,"R") && (s_flag)==0){
                    strcpy(status,"running");
                }else if(!strcmp(tmp,"T") && r_flag==0){
                    strcpy(status,"stopped");
                }
            }
        }
        printf("[%d]\t%s\t%s\t[%d]\n",i,status,Pr[i].pName,Pr[i].pId);
    }
}