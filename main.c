#include <stdio.h>
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

    if(gethostname(hostname, 20)) 
        exit(1);

    if(getlogin_r(username,20))
        exit(1);

    strcpy(actual_path,"/home/");
    strcpy(actual_path, strcat(actual_path,getlogin()));

    setenv("PWD",  actual_path, 1);
    printf("%s\n",getenv("PWD"));


    chdir(getenv("PWD"));
    setenv("OLDPWD", getenv("PWD"), 1);

    getcwd(actual_path, 1024);

    while(1)
    {
        char *opt_1;
        opt_1= (char*) malloc(sizeof(char)*1024);

        printf( ANSI_COLOR_YELLOW "%s@%s" ANSI_COLOR_RESET ":" 
                ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET "$ " ,
                getlogin(),hostname,getenv("PWD"));

        fgets(opt_1,1024,stdin);
        opt_1[strcspn(opt_1, "\r\n")] = ' ';
        opt_1=strtok(opt_1," ");

        if(opt_1!=NULL)
        {
            if(!strcmp(opt_1,"quit"))
                exit(0);

            else if(!strcmp(opt_1,"cd"))
            {
                opt_1 = strtok(NULL," ");
                if(opt_1==NULL)
                {
                    printf("%s\n",getenv("PWD"));
                }
                else
                {
                    char temp[1024];
                    if( !strcmp(opt_1,"/")   ||  !strcmp(opt_1,"/..")    |   
                            !strcmp(opt_1,"/."))
                    {
                        printf("Ruta invalida\n");
                    }
                    else if(!strcmp(opt_1,"-"))
                    {
                        chdir(getenv("OLDPWD"));
                        setenv("PWD", getenv("OLDPWD"),1);
                    }
                    else
                    {
                        if(chdir(opt_1)==-1)
                        {
                            printf("Ruta invalida\n"); 
                        }
                        else
                        {
                            getcwd(actual_path,1024);
                            setenv("OLDPWD", getenv("PWD"),1);
                            setenv("PWD", actual_path,1);
                        }
                    }
                }
            }
            else if(!strcmp(opt_1,"clr"))
            {
                printf("\033c");
            }
            else if (!strcmp(opt_1,"echo"))
            {
                opt_1 = strtok(NULL," ");
                if(opt_1!=NULL)
                {
                    if (opt_1[0]=='/' && opt_1[1]=='<') 
                    {   
                        char    *temp;
                        temp= (char*) calloc(1024,sizeof(char));
                        opt_1[0]='\r';
                        opt_1[1]='\r';

                        int i=0,
                            j=0;
                        while (1) {
                            j=0;

                            while (opt_1[j]!='\000') {
                                if (opt_1[j]!='\r'&&opt_1[j]!='$') 
                                {
                                temp[i]=opt_1[j];
                                i++;
                                }
                                j++;
                                if (opt_1[j]=='>') {
                                    i=0;
                                    break;
                                }
                            }

                            if(i==0)
                                break;

                            temp[i]=' ';
                            i++;
                            opt_1=strtok(NULL," ");
                            if (opt_1==NULL) {
                                printf("Inserte '>' para cierre");
                                break;
                            }
                        }
                        if (opt_1[2]=='$')
                        {
                            printf("%s",getenv(temp));
                        }
                        else 
                        {
                            printf("%s",temp);
                        }
                        free(temp);
                        printf("\n");
                    }    
                }
            }
        }
    }
    return 0;
}
