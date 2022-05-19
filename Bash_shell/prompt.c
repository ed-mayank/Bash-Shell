#include "shell.h"

void prompt(){
    getlogin_r(user,sizeof(user));
    gethostname(host,sizeof(host));
    getcwd(cwd,sizeof(cwd));
    int l = strlen(home);
    char* check = strstr(cwd,home);
    if(check != NULL){
        printf("<%s@%s:~%s>",user,host,&cwd[l]);
    }else{
        printf("<%s@%s:%s>",user,host,cwd);
    }
}