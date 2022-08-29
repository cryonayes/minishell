/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:13:49 by fcil              #+#    #+#             */
/*   Updated: 2022/08/29 17:35:16 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*pipeline_start(t_list *l_cmd)
{
	t_list	*iter;

	iter = l_cmd;
	while (iter)
	{
		if ((cmd_content(iter)->type & (CMD_SCMD | CMD_PIPELINE | CMD_GROUP))
			&& iter->next && cmd_content(iter->next)->type == CMD_PIPE
			&& (cmd_content(iter->next->next)->type
				& (CMD_SCMD | CMD_GROUP | CMD_PIPELINE)))
		{
			return (iter);
		}
		iter = iter->next;
	}
	return (NULL);
}

static t_list	*pipeline_end(t_list *pipeline)
{
	t_list	*iter;

	iter = pipeline;
	while (iter)
	{
		if ((cmd_content(iter)->type & (CMD_SCMD | CMD_PIPELINE | CMD_GROUP))
			&& iter->next && cmd_content(iter->next)->type == CMD_PIPE
			&& (cmd_content(iter->next->next)->type
				& (CMD_SCMD | CMD_PIPELINE | CMD_GROUP)))
		{
			iter = iter->next->next;
		}
		else
			return (iter);
	}
	return (NULL);
}

static void	pipeline_cleanup(t_cmd *c_pl, t_list *start, t_list *end)
{
	t_list	*next;
	t_list	*iter;

	iter = start;
	while (iter != end->next)
	{
		next = iter->next;
		if (cmd_content(iter)->type == CMD_PIPE)
			ft_lstdelone(iter, cmd_destroy);
		else if (cmd_content(iter)->type == CMD_PIPELINE)
		{
			ft_lstadd_back(&(c_pl->l_element), cmd_content(iter)->l_element);
			cmd_content(iter)->l_element = NULL;
			ft_lstdelone(iter, cmd_destroy);
		}
		else
		{
			ft_lstadd_back(&(c_pl->l_element), iter);
			if (iter != end)
				iter->next = NULL;
		}
		iter = next;
	}
	end->next = NULL;
}

int	parser_cmd_pipeline_merge(t_list **l_cmd)
{
	t_list	*pipeline;
	t_list	*start;
	t_list	*end;

	start = pipeline_start(*l_cmd);
	end = pipeline_end(start);
	if (!start || !end)
		return (0);
	pipeline = cmd_create(CMD_PIPELINE);
	if (pipeline == NULL)
		return (ERROR);
	lst_relink(l_cmd, pipeline, start, end);
	pipeline_cleanup(cmd_content(pipeline), start, end);
	return (1);
}
//firstly we find of pipe's left command as the start element
//later we find pipe's right command as the end element
//and we create CMD pipeline as a new CMD
//andd we delete other things...
