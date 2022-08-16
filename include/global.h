/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:45:26 by fcil              #+#    #+#             */
/*   Updated: 2022/08/16 15:12:02 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include <errno.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include "libft.h"
# include <signal.h>
# include "readline/readline.h"

# define ERROR -1
# define PROMPT "$> "
# define SHELL_NAME "minishell"

//global var
extern char	**g_env;

//env.c
int		env_init(void);
char	*env_get_val(char *name);
char	*env_find_var(char *name);
bool	is_env_var_val(char *var_name, char *val);
bool	env_is_var_char(char c);

//controlparsing.c
bool	ft_isspace(char c);
bool	ft_isquote(char c);
bool	ft_isoperator(char c);
bool	ft_isclosebracket(char c);
bool	ft_isopeningbracket(char c);

//utils.c
void	error_exit(char	*str);
char	*ft_sum_strjoin(char *src, char *str2);
void	ft_free_split(char ***split);

//utils2.c
int		print_error(char *s1, char *s2, char *s3, char *message);
int		split_count(char **str);

//signals.c
void	signalint_func(int sig);

#endif
