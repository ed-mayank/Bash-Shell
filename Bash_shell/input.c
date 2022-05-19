#include "shell.h"

char* handleSpace(char* string){
    int i=0,flag=0,index=0;
    char *temp = (char*)malloc(sizeof(char)*strlen(string));
    for(i=0;i<strlen(string);i++){
        if(string[i]=='\n')continue;
        if(!flag){
            if(string[i]==' ' || string[i]=='\t'){
                continue;
            }
            else flag=1;
        }
        if((string[i]==' ' || string[i] == '\t') && (string[i+1]==' ' || string[i+1] == '\t')){
            continue;
        }
        if(string[i]=='\t'){
            temp[index]=' ';
            index++;
            continue;
        }
        temp[index++]=string[i];
    }

    temp[index]='\0';
    return temp;
}

void input(){
    size_t size = 500;
    cmd  = (char*)malloc(sizeof(char)*size);
    int nb  = getline(&cmd,&size,stdin);
    if(nb == -1){
        printf("\n\t\t--------Quitting this Terminal--------\n");
        exit(0);
    }
    if(!strcmp(cmd,"\n"))return;
    history_wr(cmd);
    int i=0,f1=0,f2=strlen(cmd)-2,flag1=0,flag2=0;
    while(1){
        if(cmd[f1]==' ' || cmd[f1]=='\t'){
            f1++;
        }
        else flag1=1;
        if(cmd[f2]==' ' || cmd[f2]=='\t'){
            f2--;
        }
        else flag2=1;
        if(flag1 && flag2){
            break;
        }
    }
    if(cmd[f1]==';'){
        printf("Syntax Error unexpected token ';'\n");
        return;
    }
    if(cmd[f2]==';'){
        cmd[f2]='\0';
    }

    char* token = strtok(cmd,";");
    while(token != NULL){
        arguments[i] = token;
        token = strtok(NULL,";");
        i++;
    }
    int j=0;
    while(j<i){
        arguments[j] = handleSpace(arguments[j]);
        functionCall(arguments[j]);
        j++;
    }
}