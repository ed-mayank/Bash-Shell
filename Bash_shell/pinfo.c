#include "shell.h"

void pinfo(){
    int pid,flag=0;
    char ps[SIZE],pm[SIZE],pe[SIZE],pName[SIZE];
    if(!strcmp(laterPart,"")){
        pid = getpid();
        flag=1;
    }else{
        pid = atoi(laterPart);
    }
    // open the file /proc/pid/status
    FILE* f;
    char fpath[SIZE],buffer[SIZE],exeP[SIZE];
    sprintf(fpath,"/proc/%d/status",pid);
    f = fopen(fpath,"r");
    sprintf(exeP,"/proc/%d/exe",pid);
    int ex = readlink(exeP,buffer,SIZE);
    if(f==NULL || ex == -1){
        printf("No such process with pid=%d exist\n",pid);
        return;
    }
    char FR[SIZE];
    char* tk;
    int i=1;
    while(fgets(FR,SIZE,f) != NULL){
        tk = strtok(FR,":\t");
        if(!strcmp(tk,"State")){
            tk = strtok(NULL,":\t");
            strcpy(ps,tk);
        }
        else if(!strcmp(tk,"VmSize")){
            tk = strtok(NULL,":\t");
            strcpy(pm,tk);
        }else if(!strcmp(tk,"Name")){
            tk = strtok(NULL,":\t");
            strcpy(pName,tk);
        }
    }
    for(int j=strlen(buffer);j>=0;j--){
        if(buffer[j] == '/'){
            strcpy(&buffer[j+1],pName);
            break;
        }
    }
    if(strstr(buffer,home)){
        pe[0]='~';
        strcpy(&pe[1],&buffer[strlen(home)]);
    }else{
        strcpy(pe,buffer);
    }
    tk = strtok(ps," ");
    if(!bgP){
        strcat(tk,"+");
    }
    printf("pid -- %d\n",pid);
    printf("Process Status -- %s\n",tk);
    printf("memory -- %s",pm);
    printf("Executable Path -- %s\n",pe);
}