/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:42:05 by fcil              #+#    #+#             */
/*   Updated: 2022/08/28 13:15:31 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_tokenlist(char *input)
{
	t_list	*l_token;
	int		i;

	l_token = NULL;
	i = 0;
	while (input && input[i])
	{
		if (lexer_logic_op(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_pipe_op(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_parentheses_op(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_redir_op(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_text_op(input, &i, &l_token) == ERROR)
			break ;
		if (lexer_quote_op(input, &i, &l_token) == ERROR)
			break ;
		while (input[i] && ft_strchr(WHITESPACES, input[i]))
			i++;
	}
	if (input[i] != '\0')
		ft_lstclear(&l_token, c_token_destroy);
	return (l_token);
}

int	lexer_syntax_check(t_list *l_token)
{
	if (syntax_brackets(l_token) == ERROR)
		return (ERROR);
	if (syntax_bin_op(l_token) == ERROR)
		return (ERROR);
	if (syntax_pipe(l_token) == ERROR)
		return (ERROR);
	if (syntax_missing_op(l_token) == ERROR)
		return (ERROR);
	if (syntax_redir(l_token) == ERROR)
		return (ERROR);
	return (0);
}

t_list	*lexer(char *input)
{
	t_list	*l_token;

	l_token = get_tokenlist(input);
	if (l_token == NULL)
		return (NULL);
	if (lexer_syntax_check(l_token) == ERROR)
	{
		exec_exit_status_set(2);
		ft_lstclear(&l_token, c_token_destroy);
		return (NULL);
	}
	return (l_token);
}
//exec_exit_status_set -> holds exit code of the last process
//the error code is 2 in the bash syntax errors
