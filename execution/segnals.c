#include "../parsing/minishell.h"

int g_sigint = 0;

void    handler_ctrl_c(int sig)
{
    if(sig == SIGINT)
    {
        g_sigint = 1;
        rl_on_new_line();
        write(2, "\n", 1);
		rl_replace_line("", 0);
        rl_redisplay();
    }
}

// Fonction pour configurer les gestionnaires de signaux
void setup_signals(void)
{
    signal(SIGINT, handler_ctrl_c);
    signal(SIGQUIT, SIG_IGN);
}