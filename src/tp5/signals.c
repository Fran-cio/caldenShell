#include <signal.h>
void set_func_sig(__sighandler_t func)
{
    signal(SIGINT,func);
    signal(SIGTSTP,func);
    signal(SIGQUIT,func);
}
