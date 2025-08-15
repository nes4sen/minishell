#include "../minishell.h"

int     fonc_export(char **arg,  t_env **env)
{
    int     i;
    int     status;
    int     final_status;

    if(!arg)
        return(-1);
    if(!arg[1])
    {
        print_env(*env);
        return(0);
    }
    i = 1;
    final_status = 0;
    while (arg[i])
    {   
        if(has_equal_sign(arg[i]))
        {
            status = var_with_equal(arg, i, env);
        }
        else
            status = var_no_value(arg, i, env);
        if(status != 0)
            final_status = status;
        i++;
    }
    return(final_status);
}

char    *get_var_name(char *str)
{
    char    *name;
    int     i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    name = ft_substr(0, i, str);
    return (name);
}
 
int     check_var_exist_env(t_env *env, char *name)
{
    while (env)
    {
        if (ft_strcmp(env->name, name) == 0)
            return (1);
        env = env->next;
    }
    return (-1);
}

char    *get_var_value(char *str)
{
    char    *value;
    int     i;

    i = 0;
    while (str[i] && str[i] != '=')
        i++;
    if (str[i] == '=')
        value = ft_strdup(str + i + 1);
    else
        value = ft_strdup("");
    return (value);
}

int     mak_as_export(t_env **env, char *str)
{
    char    *name;
    // char    *value;

    name = get_var_name(str);
    if (!name)
        return (-1);
    // value = get_var_value(str);
    // if (!value)
    // {
    //     free(name);
    //     return (-1);
    // }
    if (check_var_exist_env(*env, name) == -1)
        add_back_env(env, name, NULL, (idx_nod(*env) + 1));
    else
        updat_env(env, name, NULL);
    // free(name);
    // free(value);
    return (0);
}

void    export_error(char *str)
{
    if (!str)
        return;
    printf("export: `%s': No such file or directory\n", str);
}

int     is_valid_name(char *str)
{
    int i;

    if(!str || !str[0])
        return (0);
    if (!ft_isalpha(str[0]) && str[0] != '_') // premier caractere doit etre une lettre
        return (0);
    i = 1;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int     has_equal_sign(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '=')
            return(1);
        i++;
    }
    return(0);
}

void    updat_env(t_env **env, char *name, char *value)
{
    t_env *current;
    
    if (!env || !name)
        return;
        
    current = *env;
    while (current)
    {
        if(ft_strcmp(name, current->name) == 0)
        {
            // free(current->value);
            if(value)
                current->value = ft_strdup(value); // Allouer nouvelle mémoire
            // Pour les variables sans valeur
            return; // Sortir après avoir trouvé et mis à jour
        }
        current = current->next;
    }
}

void    add_double_quotes(char *value, char *name, t_env *env)
{
    char    *new_str;
    int     i, j;
    
    if (!value || !name || !env)
        return;
    new_str = mm_alloc(ft_strlen(value) + 1);
    if (!new_str)
        return;
    // new_str[0] = '"';
    (1) &&(i = 1, j = 0);
    while (value[j])
        new_str[i++] = value[j++];
    // new_str[i++] = '"';
    new_str[i] = '\0';
    while (env)
    {
        if (ft_strcmp(name, env->name) == 0)
        {
            // free(env->value);
            // env->value = new_str;
            return;
        }
        env = env->next;
    }
    free(new_str);
}

void    print_env(t_env *env)
{
    while (env)
    {
        if(ft_strcmp("_", env->name) == 0)
            env = env->next;
        else if(env->value == NULL)
        {
            printf("declare -x %s\n", env->name);
            env = env->next;
        }
        else
        {
            printf("declare -x %s=\"%s\"\n", env->name, env->value);
            env = env->next;
        }
    }
}