#include "shell.h"

void bgHandle(){
    int wstatus;
    //wait for any child process
    int pid = waitpid(-1,&wstatus,WNOHANG); //WNOHANG : return immediately if no child has exited
    // printf("pid: %d from bgHandle\n",pid);
    for(int i=1;i<=prCount;i++){
        if(pid < 0){
            perror("Error");
            break;
        }
        // debug
        int exit_status = WIFEXITED(wstatus);
        int exit = WEXITSTATUS(wstatus);
        if(exit_status && pid==Pr[i].pId){
            if(!exit){
                printf("\n%s exited Normally with process id %d\n",Pr[i].pName,Pr[i].pId);
            }else{
                printf("\nExited Abnormally\n");
            }
            prompt();
            fflush(stdout);
            while(i<prCount){
                strcpy(Pr[i].pName,Pr[i+1].pName);
                Pr[i].pId = Pr[i+1].pId;
                i++;
            }
            prCount--;
        }
    }
}

void bgProcess(char *args[]){
    bgP=1;
    prCount++;
    pid_t pid;
    pid = fork();
    setpgid(0,0);
    strcpy(Pr[prCount].pName,args[0]);
    if(pid == -1){
        perror("Error");
        exit(0);
    }
    if(pid == 0){
        // printf("\nBackground Pid: %d\n",getpid());
        int status = execvp(args[0],args);
        if(status==-1){
            perror("Error");
            return;
        }
        exit(0);
    }
    Pr[prCount].pId = pid;  
}
