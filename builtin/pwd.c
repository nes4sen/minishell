#include "../minishell.h"

int		fonc_pwd(char **arg, t_env *env)
{
    if(!arg || !env)
    {
        return(1);
    }
	if(arg[1])
	{
		printf("pwd: too many arguments\n");
		return(1);
	}
	print_repert(env);
	return(0);
}

void	print_repert(t_env *env)
{
    if(!env)
    {
        printf("No environment variables set.\n");
        return;
    }
	while (env)
	{
		if(ft_strcmp("PWD", env->name) == 0)
		{
			if(env->value != NULL)
            {
				printf("%s\n", env->value);
				return;
			}	
				
		}
		env = env->next;
	}
    printf("%s\n", getcwd(NULL, 0));
}