#include "shell.h"

int history_Count(){
    FILE* fp;
    char line[SIZE];
    char fPath[SIZE];
    strcpy(fPath,home);
    strcat(fPath,"/history.txt");
    int i=0;
    fp = fopen(fPath,"r");
    if(fp < 0){
        return 0;
    }
    while(fgets(line,SIZE,fp) != NULL){
        i++;
    }
    fclose(fp);
    return i;
}

int main(int argc, char* argv[]){
    prCount=0;
    shellID=getpid();
    getcwd(home,SIZE);
    bgP=0,hCount=history_Count();
    printf("\n--------Press 'Q' to quit this shell------\n\n");
    while(1){
        fg_process = -1;
        signalHandling();
        prompt();
        input();
        if(strcmp(quit,"Q")==0){
            printf("\nHope u had a good time here. Thank you!!\n\n");
            exit(0);
        }
    }
}