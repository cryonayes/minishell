/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:07:30 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 20:48:34 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SPACE ' '
# define PROMPT "minishell>"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft.h"
# include <stdbool.h>

typedef enum e_tokenType
{
	T_FILE = 50, // ./command arg > (FILE)
	T_LITERAL,
	T_PIPE,
	T_REDIRECT,
	T_HEREDOC
}	t_tokenType;

typedef struct s_token
{
	enum e_tokenType	type;
	char				*value;
	struct s_token		*next;
	struct s_token		*previous;
}	t_token;

// tokenizer.c
void		*tokenizer(char *cmd, t_token *list);

//token_actions.c
void		token_add(t_token **first, t_token *node);
t_token		*token_create(char *value, enum e_tokenType type);
void		print_tokens(t_token *first);
void		destroy_tokens(t_token *first);

//quotes.c
char		*get_quotes(char **cmd, char column);
char		*isclosed(char **str, char c);
char		*get_envkey(char **ptr);
char		*getkeys_dquote(char	*value);
void		quotes_check(char **cmd, t_token **list);

//utils.c
void		error_exit(char	*str);
char		*ft_sum_strjoin(char *src, char *str2);

//redirect.c
void		get_operator(char **cmd, t_token **list);
int			get_operatorlen(char *str);
int			get_valueofoperator(char **value, char **cmd);

//controlparsing.c
bool		ft_isspace(char c);
bool		ft_isquote(char c);
bool		ft_isoperator(char c);
bool		ft_isclosebracket(char c);
bool		ft_isopeningbracket(char c);

#endif
