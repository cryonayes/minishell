/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:58:54 by fcil              #+#    #+#             */
/*   Updated: 2022/08/27 18:03:38 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_logic_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if ((str[*i] == '&' && str[*i + 1] == '&')
		|| (str[*i] == '|' && str[*i + 1] == '|'))
	{
		token_str = ft_substr(str, *i, 2);
		if (token_str == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_BIN_OP);
		if (token == NULL)
		{
			free(token_str);
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		*i += 2;
	}
	return (0);
}

int	lexer_pipe_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if (str[*i] == '|')
	{
		token_str = ft_substr(str, *i, 1);
		if (token_str == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_PIPE);
		if (token == NULL)
		{
			free(token_str);
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
	return (0);
}

int	lexer_parentheses_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;

	if (str[*i] == '(' || str[*i] == ')')
	{
		token_str = ft_substr(str, *i, 1);
		if (token_str == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '(')
			token = token_create(token_str, TOK_O_BRACKET);
		else
			token = token_create(token_str, TOK_C_BRACKET);
		if (token == NULL)
		{
			free(token_str);
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		(*i)++;
	}
	return (0);
}

int	lexer_redir_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = 0;
	while (ft_isdigit(str[*i + len]))
		len++;
	if (str[*i + len] == '<' || str[*i + len] == '>')
	{
		if (str[*i + len] == str[*i + len + 1])
			len++;
		len++;
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_REDIR);
		if (token == NULL)
		{
			free(token_str);
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		}
		ft_lstadd_back(l_token, token);
		*i += len;
	}
	return (0);
}
