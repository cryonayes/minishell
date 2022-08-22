/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:07:30 by fcil              #+#    #+#             */
/*   Updated: 2022/08/22 16:48:06 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "signal.h"
# include "libft.h"
# include "errno.h"
# include <readline/readline.h>
# include <readline/history.h>

# define ERROR		-1
# define NAME	"minishell"

char	**g_env;

//env.c
int		env_init(void);

//utils.c
int		split_count(char **argv);
int		print_error(char *s1, char *s2, char *s3, char *message);
void	ft_free_split(char ***split);
//signal.c
void	signal_newline(int sig);

#endif
