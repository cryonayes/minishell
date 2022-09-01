/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:56:33 by fcil              #+#    #+#             */
/*   Updated: 2022/08/30 18:32:43 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_replace_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(WHITESPACES, str[i]))
			str[i] = -1;
		i++;
	}
}
//replaces different things instead of WHITESPACES

static char	*var_needs_splitting(t_list *token)
{
	int	i;

	if (token && !(token_content(token)->flags
			& (TOK_S_QUOTE | TOK_D_QUOTE | TOK_HEREDOC)))
	{
		i = 0;
		while (token_content(token)->str[i])
		{
			if (ft_strchr(WHITESPACES, token_content(token)->str[i]))
				return (&(token_content(token)->str[i]));
			i++;
		}
	}
	return (NULL);
}

static int	var_get_splitted(t_list **l_splitted, t_list *token)
{
	t_list	*new_token;
	char	**split;
	int		i;

	var_replace_whitespaces(token_content(token)->str);
	split = ft_split(token_content(token)->str, -1);
	if (split == NULL)
		return (ERROR);
	i = 0;
	while (split[i])
	{
		new_token = token_create(split[i],
				token_content(token)->flags & ~TOK_CONNECTED);
		if (new_token == NULL)
			ft_free_split(&split);
		if (new_token == NULL)
			return (ERROR);
		ft_lstadd_back(l_splitted, new_token);
		i++;
	}
	free(split);
	if ((token_content(token)->flags & TOK_CONNECTED)
		&& str_last_chr(token_content(token)->str) != -1)
		token_content(ft_lstlast(*l_splitted))->flags |= TOK_CONNECTED;
	return (0);
}
//deletes connected flag for the token.

static void	var_token_replace(t_list **l_token, t_list *old, t_list *new)
{
	if (old == *l_token)
		*l_token = new;
	else
		lst_node_prev(*l_token, old)->next = new;
	ft_lstlast(new)->next = old->next;
	ft_lstdelone(old, c_token_destroy);
}

int	expand_var_splitting(t_list **l_token)
{
	t_list	*l_splitted;
	t_list	*iter;
	t_list	*tmp;

	iter = *l_token;
	while (iter)
	{
		tmp = iter->next;
		if (var_needs_splitting(iter) != NULL)
		{
			l_splitted = NULL;
			if (var_get_splitted(&l_splitted, iter) == ERROR)
				return (ERROR);
			if (token_content(iter)->str[0] == -1)
				token_content(
					lst_node_prev(*l_token, iter))->flags &= ~TOK_CONNECTED;
			if (l_splitted != NULL)
				var_token_replace(l_token, iter, l_splitted);
			else
				lst_node_remove(l_token, iter, c_token_destroy);
		}
		iter = tmp;
	}
	return (0);
}
