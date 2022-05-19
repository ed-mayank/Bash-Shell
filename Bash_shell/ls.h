#ifndef __LS
#define __LS
#include "shell.h"

DIR *dir;
struct dirent *sd;
void ls();
void run_ls(int a,int l,int d);
void Permissions(struct stat ss);
void numberOfLink(struct stat ss);
void owners(struct stat ss);
void fileSize(struct stat ss);
void dateTime(struct stat ss);
// struct stat ss;

#endif