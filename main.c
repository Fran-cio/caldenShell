#include <stdio.h>
//sudo apt-get install libncurses5-dev libncursesw5-dev
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc,char** argv) 
{   
    char    hostname[20],
    username[20],
    actual_path[1024],
    last_path[1024];

    strcpy(actual_path,"/home/");
    strcpy(actual_path, strcat(actual_path,getlogin()));
    strcpy(last_path,actual_path);
    chdir(actual_path);

    getcwd(actual_path, 1024);

    if(gethostname(hostname, 20)) exit(1);

    if(getlogin_r(username,20))
        exit(1);

    while(1)
    {
        char *opt_1;
        opt_1= (char*) malloc(sizeof(char)*1024);

        printf( ANSI_COLOR_YELLOW "%s@%s" ANSI_COLOR_RESET ":" 
                ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "$ " ,
                username,hostname,actual_path);

        fgets(opt_1,1024,stdin);
        opt_1[strcspn(opt_1, "\r\n")] = ' ';
        opt_1=strtok(opt_1," ");

        if(opt_1!=NULL)
        {
            if(!strcmp(opt_1,"quit"))
                exit(0);

            if(!strcmp(opt_1,"cd"))
            {
                opt_1 = strtok(NULL," ");
                if(opt_1==NULL)
                {
                    printf("%s\n",actual_path);
                }
                else
                {
                    char temp[1024];
                    strcpy(temp,actual_path);
                    if( !strcmp(opt_1,"/")   ||  !strcmp(opt_1,"/..")    |   
                            !strcmp(opt_1,"/."))
                    {
                        printf("Ruta invalida\n");
                    }
                    else if(!strcmp(opt_1,"-")){
                        chdir(last_path);
                        strcpy(actual_path,last_path);
                    }
                    else
                    {
                        if(chdir(strcat(temp,opt_1))==-1)
                        {
                            printf("Ruta invalida\n"); 
                        }
                        else
                        {
                            strcpy(last_path,actual_path);
                            strcpy(actual_path,temp);
                        }
                    }
                }
            } 
            if(!strcmp(opt_1,"clr"))
            {
                system("clear");
            }
        }
    }
    return 0;
}

