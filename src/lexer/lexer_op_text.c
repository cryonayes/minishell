/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_op_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:15:16 by fcil              #+#    #+#             */
/*   Updated: 2022/08/26 15:56:00 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	other_len(char *chr)
{
	if (*chr == '(' || *chr == ')')
		return (1);
	else if (*chr == '<' && *(chr + 1) != '<')
		return (1);
	else if (*chr == '<' && *(chr + 1) == '<')
		return (2);
	else if (*chr == '>' && *(chr + 1) != '>')
		return (1);
	else if (*chr == '>' && *(chr + 1) == '>')
		return (2);
	else if (*chr == '|' && *(chr + 1) != '|')
		return (1);
	else if (*chr == '|' && *(chr + 1) == '|')
		return (2);
	else if (*chr == '&' && *(chr + 1) == '&')
		return (2);
	return (0);
}

static int	text_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			break ;
		else if (other_len(&str[i]) > 0)
			break ;
		else if (ft_strchr("\'\"", str[i]))
			break ;
		i++;
	}
	return (i);
}

static int	quote_len(char *str)
{
	char	mark;
	int		i;

	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strchr("\'\"", str[0]) == NULL)
		return (0);
	mark = str[0];
	i = 1;
	while (str[i])
	{
		if (str[i] == mark)
			break ;
		i++;
	}
	if (str[i] != mark)
	{
		print_e(NAME, "syntax error", NULL, "unclosed quotation mark");
		return (ERROR);
	}
	return (i + 1);
}

int	lexer_text_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = text_len(&str[*i]);
	if (len > 0)
	{
		token_str = ft_substr(str, *i, len);
		if (token_str == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		token = token_create(token_str, TOK_TEXT);
		if (token == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}

int	lexer_quote_op(char *str, int *i, t_list **l_token)
{
	t_list	*token;
	char	*token_str;
	int		len;

	len = quote_len(&str[*i]);
	if (len == ERROR)
		return (ERROR);
	if (len > 0)
	{
		token_str = ft_substr(str, *i + 1, len - 2);
		if (token_str == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		if (str[*i] == '\'')
			token = token_create(token_str, TOK_TEXT | TOK_S_QUOTE);
		else
			token = token_create(token_str, TOK_TEXT | TOK_D_QUOTE);
		if (token == NULL)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		ft_lstadd_back(l_token, token);
		*i += len;
		if (!ft_strchr(WHITESPACES, str[*i]) && other_len(&str[*i]) == 0)
			token_content(token)->flags |= TOK_CONNECTED;
	}
	return (0);
}
