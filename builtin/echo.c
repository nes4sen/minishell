#include "../parsing/minishell.h"

int     echo_fonc(char **arg, int status)
{
    int i = 1;
    int flag_newline = 1;

    if(!arg || !arg[0] || !arg[i] || status > 10000000)
        return(-1);
    // vérifier s'il y a flag -n ou plusieurs -nn ou -n -n
    i = echo_check_n(arg, &flag_newline, i);
  
    while (arg[i])
    {
        printf("%s", arg[i]);
        if(arg[i + 1])
            printf(" "); // s'il y a un autre arg
        i++;
    }
    if(flag_newline)
        printf("\n");
    status = 0;
    return(0);
}

int    echo_check_n(char **arg, int *flag_newline, int i)
{
    int     j;
    int     flag_valid;

    while(arg[i] && arg[i][0] == '-' && arg[i][1] && arg[i][1] == 'n')
    {
        j = 1;
        flag_valid = 1;
        while(arg[i][j])
        {
            if(arg[i][j] != 'n')
            {
                flag_valid = 0;
                break;
            }
            j++;
        }
        if(flag_valid && j > 1) // on a plusieurs n et aussi que n 
        {
            *flag_newline = 0;
            i++;
        }
        else
            break; // on va traiter comme un argument normal
    }
    return i;
}