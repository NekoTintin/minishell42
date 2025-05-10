//* ************************************************************************** */
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

# include "../../../includes/minishell.h"


static char	**exp_add_variable(char **array, char **argument);
static int	exp_valid(char **argument);
static int	exp_var_exist(char ***array, char *string);


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
 *		->recup nom de la var;
 *		->WHILE (string[i] != "=");
 *			->i++;
 *		->WHILE(array && array[index] != NULL)
 *			->if (!ft_strncmp(array[index], string, i))
 *				->free(array[index]);
 *				->array[index] = ft_strdup(string);
 *				-> return (0);
 *		->return(1);
 *
 *
*/
static int	exp_var_exist(char ***array, char *string)
{
	int	index;
	int	n;

	index = 0;
	n = 0;
	while (string[n] && string[n] != 61)
		n++;
	while((*array)[index] != NULL)
	{
		if (!ft_strncmp((*array)[index], string, n))
		{
			free((*array)[index]);
			(*array)[index] = ft_strdup(string);
			if ((*array)[index] == NULL)
				return (-1);
			return (0);
		}
		index++;
	}
	return (1);
}

/*	FONC	exp_add_variable [arg_array, array]
 *		->create arg_array
 *		->WHILE (arg_array != NULL)
 *			-> i = var_exist(arg_array[index], array))
 *			->IF (i != 0)
 *				->change value
 *				->free(array[i])
 *				->array[i] = ft_strdup(var_array);
 *			->ELSE
 *				->add end array
 *				->array[ft_arrlen(array) + 1] = ft_strdup(var_array);
 *		return (array);
*/
static char	**exp_add_variable(char **array, char **argument)
{
	int	index;
	int	n;
	char	**new;

	new = cp_array_env(array, ft_arrlen(&argument[2]) + 1);
	if (new == NULL)
		return (NULL);
	index = 2;
	while (argument && argument[index])
	{
		n = exp_var_exist(&new, argument[index]);
		if (n == -1)
			return (NULL);
		if (n != 0)
		{
			n = ft_arrlen(new);
			new[n] = ft_strdup(argument[index]);
			if (new[n] == NULL)
				return (NULL);
		}
		index++;
	}
	free_array(array);
	new[ft_arrlen(new) + 1] = NULL;
	return (new);
}

/*
 *	FONC exp_valid [ Argument ]
 *		-> if export argument0 
 *		-> while argument[i] ! NULL
 *			->if 
 *
 *
 *
 * */
static int	exp_valid(char **argument)
{
	int	index;
	int	lenght;

	index = 2;
	while (argument != NULL && argument[index] != NULL )
	{
		lenght = 0;
		while (*argument[index] == 32)
			index++;
		if (argument[index][0] == 61)
			return (1);
		while (argument[index][lenght] != '\0' && argument[index][lenght] != 61 )
		{	
			if (lenght == 0 && !(ft_isalpha(argument[index][lenght]) || argument[index][lenght] == 95))
				return (printf("ERROR %c \n", argument[index][lenght]));
			else if (!(ft_isalpha(argument[index][lenght]) || argument[index][lenght] == 95 || ft_isdigit(argument[index][lenght])))
				return (printf("ERROR %c \n", argument[index][lenght]));
				
			lenght++;
		}
		while (argument[index] != NULL && *argument[index] != 32)
			index++;
	}
	printf("test 3\n");
	return (0);
}

/*static char	**exp_add_variable(char **array, char **argument)
{
	int	index;
	int	ind_var;
	char	**new;

	index = 0;
	ind_var = 1;
	new = cp_array_env(array, ft_arrlen(array));
	while (new[index] != NULL)
		index++;
	while (argument[ind_var] != NULL)
	{
		while (argument[ind_var] != NULL && *argument[ind_var] != 32)
			ind_var++;
		if (argument[ind_var] == NULL)
			break ;
		else
			ind_var += 1;
		new[index] = ft_strdup(argument[ind_var]);
		if (new[index] == NULL)
			return (NULL);
		ind_var++;
		index++;
	}
	free_array(array);	
	return (new);
}
