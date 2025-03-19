/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:04:02 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/18 13:55:55 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "testeur.h"


static char	**exp_add_variable(char **array, char **argument);
static int	exp_valid(char **argument);
static void	free_array(char **array);
//int	exp_var_exist(char ***array, char **argument);

/*
 *	FONC 	mini export: [array var_environement, string of argument]
 *		-> check if the var_env exist && if string of argument is valid
 *		-> add var_array [array var_environement, string of argument]
 *
*/
int	mini_export(char **argument, char ***var_env)
{
	if (argument == NULL || argument[0] == NULL)
		return (1);
	if (ft_arrlen(argument) == 1)
	{
		print_env_array(*var_env);
		return(0);
	}
	if (exp_valid(argument))
		return (1);
	*var_env = exp_add_variable(*var_env, argument);
	
	return (0);
}

/*
 *	FONC	variable_exist [array, string of argument]
 *		-> recupere le non de la variable 
 *		-> parcour le tableaux
 *			->if existe remplace 
 *		->else renvoie 0
 *
*/

/*	FONC	exp_add_variable [array, string of argument]
 *		->position sur le dernier element
 *		->ajout de la ligne avec ft_strdup(str)
 *
*/
static char	**exp_add_variable(char **array, char **argument)
{
	int	index;
	char	**new;

	index = 0;
	new = cp_array_env(array, 1);
	while (new[index] != NULL)
		index++;
	new[index] = ft_strdup(argument[1]);
	if (new[index] == NULL)
		return (NULL);
	free_array(array);	
	return (new);
}
/*
 *	FONC exp_valid [ Argument ]
 *		-> if argument 
 *
 *
 *
 *
 * */
static int	exp_valid(char **argument)
{
	int	index;
	//int	lenght;

	index = 0;
	//lenght = 0;
	if (ft_strncmp(argument[index], "export", ft_strlen("export")) != 0 \
		|| ft_strlen(argument[index]) != ft_strlen("export"))
		return (1);
	index = 1;
	printf("test 2\n");
	while (argument != NULL && argument[index] != NULL)
	{
		if (*argument[index] == 32 && index <= 1)
			return (1);
		if (*argument[index] == '=' && index > 1)
			return (1);
		index++;
	}
	printf("test 3\n");
	return (0);
}

static void	free_array(char **array)
{
	int	index;

	if (array != NULL)
	{
		index = 0;
		while (array[index] != NULL)
		{
			if (array[index] != NULL)
				free(array[index]);
			index++;
		}
		free(array);
	}
}
