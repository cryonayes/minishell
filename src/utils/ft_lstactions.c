/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstactions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:10:55 by fcil              #+#    #+#             */
/*   Updated: 2022/09/01 19:14:14 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lst_node_remove(t_list **lst, t_list *node, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !(*lst) || !node)
		return (ERROR);
	if (node == *lst)
		*lst = node->next;
	else
	{
		tmp = *lst;
		while (tmp->next && tmp->next != node)
			tmp = tmp->next;
		if (tmp->next != node)
			return (ERROR);
		tmp->next = node->next;
	}
	ft_lstdelone(node, del);
	return (0);
}

t_list	*lst_node_prev(t_list *lst, t_list *node)
{
	if (lst == node)
		return (node);
	while (lst->next && lst->next != node)
		lst = lst->next;
	if (lst->next != node)
		return (NULL);
	return (lst);
}

int	lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end)
{
	t_list	*prev;

	prev = lst_node_prev(*lst, start);
	if (prev == NULL)
		return (ERROR);
	if (start == *lst)
		*lst = node;
	else
		prev->next = node;
	if (end == NULL)
		node->next = NULL;
	else
		node->next = end->next;
	return (0);
}

void	print_tokens(t_list	*l_token)
{
	printf("\e[37;7mTOKEN:\t\t\e[m");
	if (l_token != NULL)
	{
		while (l_token->next != NULL)
		{
			if (token_content(l_token)->flags & TOK_CONNECTED)
				printf("%s \033[0;35m+ \033[m", token_content(l_token)->str);
			else
				printf("%s \033[0;32m: \033[m", token_content(l_token)->str);
			l_token = l_token->next;
		}
		printf("%s\n", token_content(l_token)->str);
	}
}
