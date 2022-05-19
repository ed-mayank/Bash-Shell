#ifndef __SHELL
#define __SHELL

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<fcntl.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<sys/stat.h>
#include<signal.h>
#include<sys/wait.h>
#include "input.h"
#define SIZE 500
#define debug printf("test\n");
//---------------------------------------------Variables------------------------------------------------------------------
char user[SIZE], host[SIZE], cwd[SIZE], home[SIZE], quit[SIZE], laterPart[SIZE], previous[SIZE], fg_processName[SIZE];
struct bgProcess{
    char pName[SIZE];
    int pId;
};
struct bgProcess Pr[SIZE];
int prCount;
int bgP;
int hCount; //history
int shellID;
int fg_process;
int fg_prompt;
int IO_flag; // redirection
int pipe_flag;
int fd1[2], fd2[2];
//------------------------------------------------------------------------------------------------------------------------
void prompt();
void echo();
void functionCall(char* commands);
char* handleSpace(char* string);
void cd();
void ls();
void systemCommand(char* commands);
void fgProcess(char* args[]);
void bgProcess(char* args[]);
void repeat();
void pinfo();
void history_re();
void history_wr(char* text);
void signalHandling();
void redirection(char* commands);
void pipeline(char* commands);
void replay();
void bgHandle();
void jobs();
void sig();
void fg();
void bg();
#endif