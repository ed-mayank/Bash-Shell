#include "shell.h"

void functionCall(char* commands){
    IO_flag=0;
    pipe_flag=0;
    char s[SIZE];
    char s1[SIZE];
    strcpy(s,commands);
    strcpy(s1,commands);
    char* token = strtok(s," ");
    char* tmp = strtok(s1," ");
    while(tmp != NULL){
        if(!strcmp(tmp,"<") || !strcmp(tmp,">") || !strcmp(tmp,">>")){
            IO_flag=1;
        }
        if(!strcmp(tmp,"|")){
            pipe_flag+=1;
        }
        tmp = strtok(NULL," ");
    }
    int i=0;
    for(i=0;i<strlen(commands);i++){
        if(token[i]!=commands[i])
        break;
    }
    
    if(commands[i] == '\0'){
        laterPart[0]='\0';
    }else{
        strcpy(laterPart,&commands[i+1]);
    }
    
    if(!strcmp(token,"replay")){
        replay();
    }
    else if(pipe_flag){
        pipeline(commands);
    }
    else if(IO_flag){
        redirection(commands);
    }
    else if(strcmp(token,"Q")==0){
        strcpy(quit,"Q\0");
    }
    else if( !strcmp(token,"echo" )){
        echo();
    }
    else if(!strcmp(token,"pwd")){
        printf("%s\n",cwd);
    }
    else if(!strcmp(token,"clear")){
        system("clear");
    }
    else if(!strcmp(token,"cd")){
        cd();
    }
    else if(!strcmp(token,"ls")){
        ls();
    }
    else if(!strcmp(token,"repeat")){
        repeat();
    }
    else if(!strcmp(token,"pinfo")){
        pinfo();
    }
    else if(!strcmp(token,"history")){
        history_re();
    }
    else if(!strcmp(token,"jobs")){
        jobs();
    }
    else if(!strcmp(token,"sig")){
        sig();
    }
    else if(!strcmp(token,"fg")){
        fg();
    }
    else if(!strcmp(token,"bg")){
        bg();
    }
    else{
        systemCommand(commands);
    }
}
