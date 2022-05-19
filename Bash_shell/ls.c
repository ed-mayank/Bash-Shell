#include "shell.h"
#include "ls.h"

void ls(){
    char* tk[SIZE];
    int i=0,a=0,l=0,d=0;
    char s[SIZE];
    strcpy(s,laterPart);
    tk[i]=strtok(s," ");
    while(tk[i]!=NULL){
        if(tk[i][0] == '-'){
            for(int j=1;j<strlen(tk[i]);j++){
                if(tk[i][j] == 'a'){
                    a=1;
                }else if(tk[i][j] == 'l'){
                    l=1;
                }
            }
        }
        else{
            d=1;
        }
        i++;
        tk[i]=strtok(NULL," ");
    }
    run_ls(a,l,d);
}

void run_ls(int a, int l,int d){
    char* tk[SIZE];
    char filePath[SIZE];
    struct stat ss;
    int i=0;
    if(d==0){
        dir = opendir(".");
        if(dir==NULL){
            perror("Error");
            return;
        }
        if(l==0){
            while((sd=readdir(dir))!=NULL){
                if(sd->d_name[0]=='.' && a==0){
                    continue;
                }
                printf("> %s\n",sd->d_name);
            }
        }
        else{
            while((sd=readdir(dir))!=NULL){
                if(sd->d_name[0]=='.' && a==0){
                    continue;
                }
                int status = stat(sd->d_name,&ss);
                if(status<0){
                    perror("Error");
                    continue;
                }
                Permissions(ss);   // permission of files
                numberOfLink(ss);  // number of links associated with files
                owners(ss);        // user owner and group owner name of files
                fileSize(ss);      // size of file
                dateTime(ss);      // date and time when file is modified
                printf("%s\n",sd->d_name);  //name of the file
            }
        }
        closedir(dir);
        return;
    }
    tk[i]=strtok(laterPart," ");
    while(tk[i]!=NULL){
        if(tk[i][0]=='-'){
            i++;
            tk[i]=strtok(NULL," ");
            continue;
        }
        if(!strcmp(tk[i],"~")){
            dir=opendir(home);
        }else{
            dir = opendir(tk[i]);
        }
        if(dir==NULL){
            perror("Error");
            return;
        }
        if(l==0){
            printf("\n%s:\n",tk[i]);
            while((sd=readdir(dir))!=NULL){
                if(sd->d_name[0]=='.' && a==0){
                    continue;
                }
                printf("> %s\n",sd->d_name);
            }
        }
        else{   // ls -l part
            while((sd=readdir(dir))!=NULL){
                if(sd->d_name[0]=='.' && a==0){
                    continue;
                }
                strcpy(filePath,tk[i]);
                strcat(filePath,"/");
                strcat(filePath,sd->d_name);
                int status = stat(filePath,&ss);
                if(status<0){
                    perror("Error");
                    i++;
                    tk[i]=strtok(NULL," ");
                    continue;
                }
                Permissions(ss);
                numberOfLink(ss);
                owners(ss);
                fileSize(ss);
                dateTime(ss);
                printf("%s\n",sd->d_name);
            }
        }
        i++;
        tk[i]=strtok(NULL," ");
    }
}

void Permissions(struct stat ss){
    ss.st_mode & S_IFDIR ? printf("d") : printf("-");
    ss.st_mode & S_IRUSR ? printf("r") : printf("-");
    ss.st_mode & S_IWUSR ? printf("w") : printf("-");
    ss.st_mode & S_IXUSR ? printf("x") : printf("-");
    ss.st_mode & S_IRGRP ? printf("r") : printf("-");
    ss.st_mode & S_IWGRP ? printf("w") : printf("-");
    ss.st_mode & S_IXGRP ? printf("x") : printf("-");
    ss.st_mode & S_IROTH ? printf("r") : printf("-");
    ss.st_mode & S_IWOTH ? printf("w") : printf("-");
    ss.st_mode & S_IXOTH ? printf("x") : printf("-");
    printf(" ");
}

void numberOfLink(struct stat ss){
    printf("%ld ",ss.st_nlink);
}

void owners(struct stat ss){
    struct passwd *pw = getpwuid(ss.st_uid);
    struct group *gr = getgrgid(ss.st_gid);
    printf("%s %s ",pw->pw_name,gr->gr_name);
}

void fileSize(struct stat ss){
    printf("%-8ld",ss.st_size);
}

void dateTime(struct stat ss){
    struct tm dt;
    char dte[SIZE];
    strftime(dte,SIZE,"%b %d %H:%M",localtime(&ss.st_mtime));
    printf("%s ",dte);
}