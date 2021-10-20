#include <signal.h>
/*
 * Agrega un handler a las 3 señales que se piden en las consigas
 * SIG_IGN: Ignora la señal.
 * SIG_DFL: Mantiene de manera por defecto.
 */
void set_func_sig(__sighandler_t func)
{
    signal(SIGINT,func);
    signal(SIGTSTP,func);
    signal(SIGQUIT,func);
}
