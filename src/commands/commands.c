/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 18:07:05 by fcil              #+#    #+#             */
/*   Updated: 2022/08/27 18:01:00 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*cmd_create(int type)
{
	t_cmd	*cmd;
	t_list	*l_cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = type;
	cmd->l_element = NULL;
	l_cmd = ft_lstnew(cmd);
	if (l_cmd == NULL)
	{
		cmd_destroy(l_cmd);
		return (NULL);
	}
	l_cmd->next = NULL;
	return (l_cmd);
}

t_cmd	*cmd_content(t_list *cmd)
{
	return ((t_cmd *)cmd->content);
}

void	cmd_destroy(void *cmd)
{
	if (((t_cmd *)cmd)->type == CMD_SCMD)
		scmd_destroy(cmd);
	else
	{
		if (((t_cmd *)cmd)->l_element)
			ft_lstclear(&(((t_cmd *)cmd)->l_element), cmd_destroy);
		free(cmd);
	}
}

int	cmd_type(t_list *cmd)
{
	return (*(int *)(cmd->content));
}

int	cmd_type_from_token(t_list *token)
{
	if (token == NULL)
		return (ERROR);
	else if (token_content(token)->flags & (TOK_TEXT | TOK_REDIR))
		return (CMD_SCMD);
	else if (token_content(token)->flags & TOK_BIN_OP)
	{
		if (token_content(token)->str[0] == '&')
			return (CMD_AND);
		else if (token_content(token)->str[0] == '|')
			return (CMD_OR);
	}
	else if (token_content(token)->flags & TOK_PIPE)
		return (CMD_PIPE);
	else if (token_content(token)->flags & TOK_O_BRACKET)
		return (CMD_O_BRACKET);
	else if (token_content(token)->flags & TOK_C_BRACKET)
		return (CMD_C_BRACKET);
	return (ERROR);
}
//shortly we create differents ids for CMD(parser) from the TOKENS.
//it's like a clone of TOKENS
