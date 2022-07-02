/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:00:57 by aeser             #+#    #+#             */
/*   Updated: 2022/07/02 17:46:12 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINISHELL
# define H_MINISHELL

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
	TOKEN_TYPE_LAST
} t_tokenType;

typedef enum e_operator
{
	T_PIPE = TOKEN_TYPE_LAST,
	T_REDIRECT
} t_operator;

typedef struct s_token
{
	enum e_tokenType	type;
	char				*value;
	struct s_token		*next;
	struct s_token		*previous;
} t_token;

// tokenizer.c
t_token		*tokenizer(char *cmd);

//token_actions.c
t_token		*token_init(t_token *stack)
void	token_add(t_token *stack, char *node);

#endif
