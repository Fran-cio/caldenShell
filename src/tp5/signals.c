#include <signal.h>
#include <sys/wait.h>
/*
 * Agrega un handler a las 3 señales que se piden en las consigas
 * SIG_IGN: Ignora la señal.
 * SIG_DFL: Mantiene de manera por defecto.
 * sigHandler: Un handler asignado a el fin de un proc hijo
 */
void set_func_sig(__sighandler_t func)
{
    signal(SIGINT,func);
    signal(SIGTSTP,func);
    signal(SIGQUIT,func);
}

void sigHandler(int signum){
    int status;
     switch(signum){
        case SIGCHLD:
             waitpid(-1, &status, WNOHANG);
             break;
     }
}
