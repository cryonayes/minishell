/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 17:58:31 by fcil              #+#    #+#             */
/*   Updated: 2022/08/27 17:53:10 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*scmd_create(int type)
{
	t_scmd		*scmd;
	t_list		*l_scmd;

	scmd = malloc(sizeof(t_scmd));
	if (scmd == NULL)
		return (NULL);
	scmd->type = type;
	scmd->l_argv = NULL;
	scmd->l_redir = NULL;
	l_scmd = ft_lstnew(scmd);
	if (l_scmd == NULL)
	{
		scmd_destroy(scmd);
		return (NULL);
	}
	l_scmd->next = NULL;
	return (l_scmd);
}

t_scmd	*scmd_content(t_list *scmd)
{
	return ((t_scmd *)scmd->content);
}

void	scmd_destroy(void *scmd)
{
	if (((t_scmd *)scmd)->l_argv)
		ft_lstclear(&(((t_scmd *)scmd)->l_argv), c_token_destroy);
	if (((t_scmd *)scmd)->l_redir)
		ft_lstclear(&(((t_scmd *)scmd)->l_redir), c_token_destroy);
	free(scmd);
}
