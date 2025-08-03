#include "../minishell.h"

int     unset_fonc(char **arg, t_env **env)
{
    int     i;
    int     idex;

	if(arg[1] == NULL)
		return(0);
    i = 1;
    while (arg[i])
    {
        idex = find_idex_var_env(arg[i], *env);
        if(idex != -1)
        {
            delete_var_env(idex, env);
            indx_nods(env);
        }
        i++;
    }
    return(0);
}

int     find_idex_var_env(char *str, t_env *env)
{
    char *name;

    if(!str || !env)
        return(-1);
    name = get_var_name(str);
    if(!name)
        return(-1); 
    while(env)
    {
        if(ft_strcmp(env->name, name) == 0)
            return(free(name), env->index);
        env = env->next;
    }
    free(name);
    return(-1);
}

void     indx_nods(t_env **env)
{
    t_env *temp;
    int     i = 0;

    if(!env || !*env)
        return;
    temp = *env;
    while (temp != NULL)
    {
        temp->index = i++;
        temp = temp->next;
    }
}

void	delete_var_env(int idx, t_env **env)
{
    t_env *env_temp;
    t_env *temp;

	indx_nods(env);
    if(idx == 0)
        delete_first_node(env);
    env_temp = *env;
	while (env_temp != NULL)
	{
		if(idx - env_temp->index == 1)
		{
            temp = env_temp->next;
			if(env_temp->next->next == NULL)
				env_temp->next = NULL;
			else 
				env_temp->next = env_temp->next->next;
            free(temp->name);
            free(temp->value);
            free(temp);
			break;
		}
		env_temp = env_temp->next;
	}
    indx_nods(env);
}

void    delete_first_node(t_env **env)
{
    t_env   *temp;

    temp = *env;
    *env = (*env)->next;
    free(temp->name);
    free(temp->value);
    free(temp);
    indx_nods(env);
    return ;
}
