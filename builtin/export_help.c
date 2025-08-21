#include "../parsing/minishell.h"

char	*get_var_value(char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		value = ft_strdup(str + i + 1);
	else
		value = ft_strdup("");
	return (value);
}

int	mak_as_export(t_env **env, char *str)
{
	char	*name;

	name = get_var_name(str);
	if (!name)
		return (-1);
	if (check_var_exist_env(*env, name) == -1)
		add_back_env(env, name, NULL, (idx_nod(*env) + 1));
	else
		updat_env(env, name, NULL);
	return (0);
}

void	export_error(char *str)
{
	if (!str)
		return ;
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
}

int	has_equal_sign(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}