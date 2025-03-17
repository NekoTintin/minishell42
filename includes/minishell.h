/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:08:17 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 20:13:03 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "lexer.h"
# include "parsing.h"
# include "exec.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <term.h>
# include <errno.h>

# define ERR_ARG "minishell don't need arguments. Use './minishell' instead."
// functions in pwd.c
char		*ft_pwd(void);

// functions in pars_utils.c
char		*ft_get_from_env(char *env_var, char **envp);

#endif
