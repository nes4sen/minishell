/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-laf <aait-laf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:18:47 by aait-laf          #+#    #+#             */
/*   Updated: 2025/06/22 15:10:31 by aait-laf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *dest, char *src)
{
	char	*p;
	size_t	i;
	size_t	j;

	if (!dest || !src)
		return (NULL);
	i = 0;
	j = 0;
	p = mm_alloc(ft_strlen((char *)dest) + ft_strlen((char *)src) + 1);
	if (!p)
		return (NULL);
	while (dest[i] != '\0')
	{
		p[i] = dest[i];
		i++;
	}
	while (src[j] != '\0')
	{
		p[i + j] = src[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}

void    print_str(char *str)
{
    int     i;

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

int	ft_isalnum(int c)
{
	return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z'))
		|| ((c >= 'a') && (c <= 'z')));
}

int	ft_isalpha(int c)
{
	return (!(c > 122 || (c < 97 && c > 90) || c < 65));
}

int	ft_isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = mm_alloc(ft_strlen((char *)s1) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int ft_strncmp(char *s1, char *s2, size_t n)
{
    size_t i;

	if (!s1 || !s2)
		return (1);
    i = 0;
    while (i < n && s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (1);
        i++;
    }
    if (i < n)
        return (s1[i] != s2[i]);
    return (0);
}

int ft_atoi(const char *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    if (!str)
        return (0);
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || 
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

char **env_to_char_array(t_env *env)
{
    int count = 0;
    t_env *temp = env;
    char **env_array;
    int i = 0;
    
    if (!env)
        return NULL;
    
    // Compter le nombre de variables
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    
    // Allouer le tableau
    env_array = mm_alloc(sizeof(char *) * (count + 1));
    if (!env_array)
        return NULL;
    
    // Remplir le tableau
    temp = env;
    while (temp)
    {
        // Calculer la taille nécessaire: name + "=" + value + '\0'
        int len = ft_strlen(temp->name) + 1 + ft_strlen(temp->value) + 1;
        env_array[i] = malloc(len);
        if (!env_array[i])
        {
            // free_env_array(env_array);
            return NULL;
        }
        
        // Construire la chaîne "NAME=VALUE"
        ft_strcpy(env_array[i], temp->name);
        ft_strcat(env_array[i], "=");
        ft_strcat(env_array[i], temp->value);
        
        i++;
        temp = temp->next;
    }
    env_array[i] = NULL;
    
    return env_array;
}

void free_env_array(char **env_array)
{
    int i = 0;
    
    if (!env_array)
        return;
    
    while (env_array[i])
    {
        free(env_array[i]);
        i++;
    }
    free(env_array);
}

char *ft_strcat(char *dest, const char *src)
{
    int i = 0;
    int j = 0;
    
    while (dest[i])
        i++;
    while (src[j])
    {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
    return dest;
}

int		idx_nod(t_env *env)
{
    int i;

    i = 0;
    while (env)
    {
        env->index = i++;
        env = env->next;
    }
    return(i);
}