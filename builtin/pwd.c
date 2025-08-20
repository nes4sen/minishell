#include "../parsing/minishell.h"

int		fonc_pwd(char **arg, t_env *env)
{
    if(!arg || !env)
    {
        return(1);
    }
	if(arg[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return(1);
	}
	print_repert(env);
	return(0);
}

void	print_repert(t_env *env)
{
	char	*result;

    if(!env)
    {
        ft_putstr_fd("No environment variables set.\n", 2);
        return;
    }
	result = getcwd(NULL, 0);
	if(!result)
	{
		perror("getcwd");
		return;
	}
	ft_putstr_fd(result, 1), ft_putstr_fd("\n", 1);
	free(result);
}