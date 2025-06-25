/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:08:17 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/25 12:58:46 by qupollet         ###   ########.fr       */
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
# include <stdbool.h>
# include <linux/limits.h>

# define ERR_ARG "minishell don't need arguments. Use './minishell' instead."

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_minishell
{
	char		*line;
	t_lexer		*lexer;
	t_parser	*parse;
	t_env		*env;
	bool		status;
}	t_minishell;

void			get_val_tenv(int code, t_lexer *lexer, t_env *env);
t_minishell		*mini_init(char **envp);
void			mini_free(t_minishell *mini);
int				mini_exec_line(t_minishell *mini, int *code_error);

/* *************************************************** */

extern int	g_sig;

void			sig_setup_mini(void);
void			sig_setup_defaut(void);

/* *************************************************** */

// functions in env_init.c
t_env			*ft_create_tenv(char **envp);
void			ft_free_env(t_env *top);

// functions in env_func.c
int				ft_add_to_env(t_env *top, char *key, char *val);
char			*ft_env_get_value(t_env *env, char *key);
char			**ft_env_to_tab(t_env *env);
int				env_remove(t_env **env, char *key);

// functions in env_utils.c
int				exec_env_size(t_env *env);
void			free_tab(char **tablo);

#endif
