#include "../parsing/minishell.h"

int	fonc_cd(char **arg, t_env *env)
{
	char	*tmp;
	char	*current_getcwd;
	char	*pwd_now;
	int		nombre_arg;
	int		status;

	tmp = NULL;
	current_getcwd = NULL;
	if (!arg)
		return (-1);
	nombre_arg = get_nbr_arg(arg);
	pwd_now = find_home_repert(env, "PWD");
	if (nombre_arg == 1)
		status = cd_zero_arg(tmp, pwd_now, current_getcwd, env);
	else if (nombre_arg == 2)
		status = cd_with_arg(arg, pwd_now, current_getcwd, env);
	else
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (-1);
	}
	return (status);
}

void	update_env(t_env **env, const char *name, const char *value)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->name, (char *)name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	add_back_env(env, (char *)name, (char *)value, (idx_nod(*env) + 1));
}

int	get_nbr_arg(char **arg)
{
	int i = 0;

	while (arg[i])
		i++;
	return (i);
}