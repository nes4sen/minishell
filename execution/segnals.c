#include "../minishell.h"

void    handler_ctrl_c(int sig)
{
    if(sig == SIGINT)
    {
        write(1, "\n", 1);
		rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

// Fonction pour configurer les gestionnaires de signaux
void setup_signals(void)
{
    signal(SIGINT, handler_ctrl_c);
    signal(SIGQUIT, SIG_IGN);
}