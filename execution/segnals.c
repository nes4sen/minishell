#include "../minishell.h"

void    handler_ctrl_c(int sig)
{
    if(sig == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    handler_ctrl_d(int sig)
{
    (void)sig;
    exit(0);
}

void    handler_ctrl_slash(int sig)
{
    (void)sig;
}

// Fonction pour configurer les gestionnaires de signaux
void setup_signals(void)
{
    signal(SIGINT, handler_ctrl_c);
    signal(SIGQUIT, handler_ctrl_slash);
}