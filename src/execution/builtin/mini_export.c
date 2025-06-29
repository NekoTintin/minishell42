/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:27:33 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/28 17:24:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**m_exp_tab(char **arg);

int	mini_export_is_valid(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	mini_export_split(char *str, char **key, char **val)
{
	char		*splited;

	splited = ft_strchr(str, '=');
	if (splited)
	{
		*key = ft_substr(str, 0, splited - str);
		*val = ft_strdup(splited + 1);
	}
	else
	{
		*key = ft_strdup(str);
		*val = NULL;
	}
}

int	mini_export_content(t_env *env, char *str)
{
	char		*key;
	char		*val;
	int			ret;

	key = NULL;
	val = NULL;
	ret = 0;
	mini_export_split(str, &key, &val);
	if (!key)
	{
		if (!val)
			free(val);
		return (perror("malloc"), EXIT_FAILURE);
	}
	if (ft_add_to_env(env, key, val) != 0)
	{
		write(2, "bash: export: cannot add ", 26);
		write(2, key, ft_strlen(key));
		write(2, " to env\n", 9);
		ret = EXIT_FAILURE;
	}
	free(key);
	free(val);
	return (ret);
}

void	mini_export_print(char *str, int *ret)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*ret = EXIT_FAILURE;
}

int	mini_export(char **args, t_env *env)
{
	char	**tablo;
	int		idx;
	int		code;
	int		ret;

	tablo = m_exp_tab(args);
	if (!tablo)
		return (perror("malloc"), EXIT_FAILURE);
	if (!tablo[1])
		return (0);
	idx = 1;
	ret = 0;
	while (tablo[idx])
	{
		if (!mini_export_is_valid(tablo[idx]))
			mini_export_print(tablo[idx], &ret);
		else
		{
			code = mini_export_content(env, tablo[idx]);
			if (code != 0)
				ret = code;
		}
		idx++;
	}
	return (free_tab(tablo), ret);
}

char    **copy_tab(char **src)
{
    int     i;
    char    **copy;

    if (!src)
        return (NULL);

    // Compter le nombre de chaînes dans src
    i = 0;
    while (src[i])
        i++;

    // Allouer le tableau + NULL final
    copy = malloc(sizeof(char *) * (i + 1));
    if (!copy)
        return (NULL);

    // Copier chaque chaîne
    i = 0;
    while (src[i])
    {
        copy[i] = ft_strdup(src[i]);
        if (!copy[i])
        {
            // Libération en cas d'erreur
            while (--i >= 0)
                free(copy[i]);
            free(copy);
            return (NULL);
        }
        i++;
    }
    copy[i] = NULL;
    return (copy);
}

char	**m_exp_tab(char **args)
{
	char	*join;
	char	**array;

	join = NULL;
	array = NULL;
	if(args[1][ft_strlen(args[1]) - 1] != '=')
		return (copy_tab(args));
	join = ft_strjoin(args[1],args[2]);
	if (join == NULL)
		return(NULL);
	array = (char **)malloc(sizeof(char *) * 3);
	if (array == NULL)
		return (free(join),NULL);
	array[0] = ft_strdup(args[0]);
	if (array[0]== NULL)
		return(free(array),free(join),NULL);
	array[1] = ft_strdup(join);
	if (array[1] == NULL)
		return (free(array),free(join),NULL);
	array[2] = NULL;
	return (free(join),array);

}
