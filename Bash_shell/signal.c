#include "shell.h"

void ctrl_C(int signum)
{
    printf("\n");
    if (fg_process == -1)
    {
        prompt();
        fflush(stdout);
        return;
    }
    if (fg_process >= 0)
    {
        kill(fg_process, SIGKILL);
    }
}

void ctrl_Z()
{
    if (fg_process == shellID)
    {
        return;
    }
    if (fg_process == -1)
    {
        fflush(stdout);
    }
    else
    {
        
        kill(fg_process, SIGTTIN);
        kill(fg_process, SIGTSTP);
        prCount++;
        Pr[prCount].pId=fg_process;
        strcpy(Pr[prCount].pName,fg_processName);
        
    }
    fflush(stdout);
}

void signalHandling()
{
    signal(SIGCHLD, bgHandle);
    signal(SIGINT, ctrl_C);
    signal(SIGTSTP, ctrl_Z);
    return;
}