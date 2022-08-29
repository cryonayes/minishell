/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:21:37 by fcil              #+#    #+#             */
/*   Updated: 2022/08/29 18:15:09 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	scmd_token_set(t_scmd *c_scmd, t_list **l_token)
{
	t_list	*next;

	while (cmd_type_from_token(*l_token) == CMD_SCMD)
	{
		next = (*l_token)->next;
		if (token_content(*l_token)->flags & TOK_REDIR)
		{
			if (redir_type(token_content(*l_token)->str) == REDIR_HEREDOC)
			{
				if (parser_heredoc(*l_token) == ERROR)
					return (ERROR);
			}
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		}
		else if (token_content(*l_token)->flags & TOK_REDIR_FILE)
			ft_lstadd_back(&(c_scmd->l_redir), *l_token);
		else
			ft_lstadd_back(&(c_scmd->l_argv), *l_token);
		(*l_token)->next = NULL;
		*l_token = next;
	}
	return (0);
}

t_list	*parser_scmd_tokens(t_list *l_token)
{
	t_list	*l_scmd;
	t_list	*scmd;
	t_list	*next;

	l_scmd = NULL;
	while (l_token != NULL)
	{
		scmd = scmd_create(cmd_type_from_token(l_token));
		if (scmd == NULL || (scmd_content(scmd)->type == CMD_SCMD
				&& scmd_token_set(scmd_content(scmd), &l_token) == ERROR))
		{
			ft_lstclear(&l_scmd, scmd_destroy);
			return (NULL);
		}
		if (scmd_content(scmd)->type != CMD_SCMD)
		{
			next = l_token->next;
			ft_lstdelone(l_token, c_token_destroy);
			l_token = next;
		}
		ft_lstadd_back(&l_scmd, scmd);
	}
	return (l_scmd);
}
//firstly gets type from the l_token
//after that creates new list element
//Separate scmd from other token

static int	parser_recursive_merge(t_list **l_cmd)
{
	int	group;
	int	pipeline;

	group = 1;
	pipeline = 1;
	while (group > 0 || pipeline > 0)
	{
		group = parser_cmd_group_merge(l_cmd);
		if (group == ERROR)
			return (ERROR);
		printer_structure(*l_cmd);//log
		pipeline = parser_cmd_pipeline_merge(l_cmd);
		if (pipeline == ERROR)
			return (ERROR);
		printer_structure(*l_cmd);//log
	}
	return (0);
}

t_list	*parser(t_list *l_token)
{
	t_list	*l_cmd;

	print_tokens(l_token);
	l_cmd = parser_scmd_tokens(l_token);
	if (l_cmd == NULL)
		return (NULL);
	printer_cmd(l_cmd); //log
	printer_structure(l_cmd);//log
	if (parser_recursive_merge(&l_cmd) == ERROR)
	{
		ft_lstclear(&l_cmd, cmd_destroy);
		return (NULL);
	}
	return (l_cmd);
}
