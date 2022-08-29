/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:45:07 by fcil              #+#    #+#             */
/*   Updated: 2022/08/26 16:52:02 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define ERR_LIST	"incomplete command list"

int	syntax_bin_op(t_list *l_token)
{
	if (l_token && token_content(l_token)->flags & TOK_BIN_OP)
		return (print_e(NAME, "syntax error", NULL, ERR_LIST));
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_BIN_OP)
		{
			if (l_token->next == NULL)
				return (print_e(NAME, "syntax error", NULL, ERR_LIST));
			else if (token_content(l_token->next)->flags
				& (TOK_BIN_OP | TOK_PIPE | TOK_C_BRACKET))
				return (print_e(NAME, "syntax error", NULL, ERR_LIST));
		}
		if (token_content(l_token)->flags & TOK_O_BRACKET)
		{
			if (l_token->next
				&& token_content(l_token->next)->flags & TOK_BIN_OP)
				return (print_e(NAME, "syntax error", NULL, ERR_LIST));
		}
		l_token = l_token->next;
	}
	return (0);
}

int	syntax_pipe(t_list *l_token)
{
	if (l_token && token_content(l_token)->flags & TOK_PIPE)
		return (print_e(NAME, "syntax error", NULL, "incomplete pipe"));
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_PIPE)
		{
			if (l_token->next == NULL)
				return (print_e(NAME, "syntax error", NULL, "incomplete pipe"));
			else if (token_content(l_token->next)->flags
				& (TOK_BIN_OP | TOK_PIPE | TOK_C_BRACKET))
				return (print_e(NAME, "syntax error", NULL, "incomplete pipe"));
		}
		if (token_content(l_token)->flags & TOK_O_BRACKET)
		{
			if (l_token->next && token_content(l_token->next)->flags & TOK_PIPE)
				return (print_e(NAME, "syntax error", NULL, "incomplete pipe"));
		}
		l_token = l_token->next;
	}
	return (0);
}

int	syntax_brackets(t_list *l_token)
{
	int	count;

	count = 0;
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_O_BRACKET)
		{
			count++;
			if (l_token->next
				&& token_content(l_token->next)->flags & TOK_C_BRACKET)
			{
				print_e(NAME, "syntax error", NULL, "empty brackets");
				return (ERROR);
			}
		}
		else if (token_content(l_token)->flags & TOK_C_BRACKET)
			count--;
		if (count < 0)
			return (print_e(NAME, "syntax error", NULL, "unopened brackets"));
		l_token = l_token->next;
	}
	if (count > 0)
		return (print_e(NAME, "syntax error", NULL, "unclosed brackets"));
	return (0);
}

int	syntax_missing_op(t_list *l_token)
{
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_C_BRACKET
			&& l_token->next
			&& token_content(l_token->next)->flags & TOK_O_BRACKET)
			return (print_e(NAME, "syntax error", NULL, "missing operator"));
		else if (token_content(l_token)->flags & TOK_C_BRACKET
			&& token_is_cmd(l_token->next))
			return (print_e(NAME, "syntax error", NULL, "missing operator"));
		else if (token_is_cmd(l_token)
			&& l_token->next
			&& token_content(l_token->next)->flags & TOK_O_BRACKET)
			return (print_e(NAME, "syntax error", NULL, "missing operator"));
		l_token = l_token->next;
	}
	return (0);
}
//check mising operators between texts and brackets 
//exs: cmd(cmd) -> err. (cmd)(cmd) -> err. (cmd)cmd -> err

int	syntax_redir(t_list *l_token)
{
	while (l_token)
	{
		if (token_content(l_token)->flags & TOK_REDIR)
		{
			if (l_token->next == NULL
				|| !(token_content(l_token->next)->flags & TOK_TEXT))
			{
				print_e(NAME, "syntax error", NULL, "invalid redirection");
				return (ERROR);
			}
			l_token = l_token->next;
			token_content(l_token)->flags |= TOK_REDIR_FILE;
			while (token_content(l_token)->flags & TOK_CONNECTED)
			{
				token_content(l_token->next)->flags |= TOK_REDIR_FILE;
				l_token = l_token->next;
			}
		}
		l_token = l_token->next;
	}
	return (0);
}
