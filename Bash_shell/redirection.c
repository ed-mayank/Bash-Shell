#include "shell.h"

void redirection(char *commands)
{
    int in_desc = dup(0);
    int out_desc = dup(1);
    int r = 0, w = 0, a = 0, f = 0;
    int fd;
    char txt[SIZE];
    strcpy(txt, "\0");
    char *cmnd;
    char *rd = strstr(commands, "<");
    char *wr = strstr(commands, ">");
    char *ap = strstr(commands, ">>");
    if(rd!=NULL && wr!=NULL){
        char c[SIZE];
        c[0]='\0';
        int g=0,a=0;
        char* tk = strtok(commands," ");
        while(tk!=NULL){
            if(!strcmp(tk,"<")) a=1;
            strcat(c," ");
            if(g){
                strcat(c,tk);
                strcat(c," | grep .");
                g=0;
                a=0;
            }else{
                strcat(c,tk);
            }
            if(a)g=1;
            tk=strtok(NULL," ");
        }
        pipeline(c);
        return;
    }
    char *token = strtok(commands, " ");
    while (token != NULL)
    {
        if (r)
        {
            f = 1;
            fd = open(token, O_RDONLY);
            if (fd < 0)
            {
                perror("Error");
                return;
            }
            cmnd = handleSpace(txt);

            if (dup2(fd, 0) < 0)
            {
                perror("Duplication error");
                return;
            }
            close(fd);
            functionCall(cmnd);
            dup2(in_desc, 0);
            close(in_desc);
            close(out_desc);

            r = 0;
            strcpy(txt, "\0");
        }
        else if (a || w)
        {
            f = 1;
            if (w)
            {
                fd = open(token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                w = 0;
            }
            else if (a)
            {
                fd = open(token, O_CREAT | O_WRONLY | O_APPEND, 0644);
                a = 0;
            }

            cmnd = handleSpace(txt);
            if (dup2(fd, 1) < 0)
            {
                perror("Unable to duplicate file descriptor");
                return;
            }
            close(fd);
            functionCall(cmnd);
            dup2(out_desc, 1);
            close(in_desc);
            close(out_desc);
            strcpy(txt, "\0");
        }

        if (!strcmp(token, "<"))
        {
            r = 1;
        }
        else if (!strcmp(token, ">"))
            w = 1;
        else if (!strcmp(token, ">>"))
            a = 1;
        if (f)
        {
            f = 0;
        }
        else if (!a && !r && !w)
        {
            strcat(txt, " ");
            strcat(txt, token);
        }
        token = strtok(NULL, " ");
    }
}