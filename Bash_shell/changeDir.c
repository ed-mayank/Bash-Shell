#include "shell.h"

void cd(){
        char temp[SIZE];
    if(!strcmp(laterPart,"")){
       getcwd(previous,SIZE);
       chdir(home);
       return;
    }
    if(!strcmp(laterPart,"-")){
        getcwd(temp,SIZE);
        printf("%s\n",previous);
        chdir(previous);
        strcpy(previous,temp);
        return;
    }
    if(!strcmp(laterPart,"~")){
        strcpy(previous,cwd);
        chdir(home);
        return;
    }
    if(laterPart[0]=='/'){
        strcpy(temp,cwd);
        if(chdir(laterPart)<0){
            printf("Error: No such file or directory\n");
        }else{
            strcpy(previous,temp);
        }
    }
    else{
        char s[SIZE];
        strcpy(s,cwd);
        strcpy(temp,cwd);
        strcat(temp,"/");
        strcat(temp,laterPart);
        if(chdir(temp)<0){
            printf("Error: No such file or directory\n");
        }else{
            strcpy(previous,s);
        }
    }
}