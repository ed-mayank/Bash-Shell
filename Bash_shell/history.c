#include "shell.h"

void history_wr(char* text){
    FILE* fp;
    char fPath[SIZE];
    strcpy(fPath,home);
    strcat(fPath,"/history.txt");
    if(hCount < 20){
        fp = fopen(fPath,"a");
        if(fp == NULL){
            printf("Error\n");
            return;
        }
        fprintf(fp,"%s",text);
        fclose(fp);
        hCount++;
    }
    else{
        fp = fopen(fPath,"r");
        char temp[21][SIZE];
        int i=0;
        char l[SIZE];
        while(fgets(l,SIZE,fp)!=NULL){
            strcpy(temp[i],l);
            i++;
        }
        fclose(fp);
        remove(fPath);
        fp = fopen(fPath,"a");
        for(int j=1;j<i;j++){
            fprintf(fp,"%s",temp[j]);
        }
        fprintf(fp,"%s",text);
        fclose(fp);
    }
}

void history_re(){
    FILE* fp;
    char fPath[SIZE];
    strcpy(fPath,home);
    strcat(fPath,"/history.txt");
    fp = fopen(fPath,"r");
    int i=1;
    char his[SIZE];
    if(!strcmp(laterPart,"")){
        while(fgets(his,SIZE,fp)!=NULL){
            if(hCount<10){
                printf("%s",his);
            }else{
                if(hCount < 20){
                    if(hCount-i <=10){
                        printf("%s",his);
                    }
                }else{
                    if(i>10 && i<=20){
                        printf("%s",his);
                    }
                }
            }
            i++;
        }
        fclose(fp);
    }else{
        int k = atoi(laterPart);
        if(k<0){
            printf("Error: Invalid command\n");
            return;
        }
        while(fgets(his,SIZE,fp)!=NULL){
            if(hCount<k){
                printf("%s",his);
            }else{
                if(hCount < 20){
                    if(hCount-i <=k){
                        printf("%s",his);
                    }
                }else{
                    if(i>=(hCount-k)){
                        printf("%s",his);
                    }
                }
            }
            i++;
        }
        fclose(fp);
    }
}

// Bonus part1 and part2