/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 05:28:37 by fcil              #+#    #+#             */
/*   Updated: 2022/08/31 06:13:53 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_token_is_wildcard(t_list *token)
{
	while (token && token_content(token)->flags & TOK_CONNECTED)
	{
		if (!(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
			&& ft_strchr(token_content(token)->str, '*'))
			return (1);
		token = token->next;
	}
	if (token && !(token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
		&& ft_strchr(token_content(token)->str, '*'))
		return (1);
	return (0);
}
//if there is * in our token, its wildcard

char	*expand_pattern_get(t_list *token)
{
	char	*wildcard;

	wildcard = ft_strdup("");
	if (wildcard == NULL)
		return (NULL);
	while (token && token_content(token)->flags & TOK_CONNECTED)
	{
		wildcard = expand_wildcard_append_str(wildcard, token);
		if (wildcard == NULL)
			return (NULL);
		token = token->next;
	}
	wildcard = expand_wildcard_append_str(wildcard, token);
	if (wildcard == NULL)
		return (NULL);
	return (wildcard);
}
//returns str of our token but changes * to -1 in expand_wildcard_append_str

char	*expand_wildcard_append_str(char *wildcard, t_list *token)
{
	char	*str;
	int		i;

	str = token_content(token)->str;
	if (token_content(token)->flags & (TOK_D_QUOTE | TOK_S_QUOTE))
		return (str_append_str(wildcard, str));
	i = 0;
	while (str[i])
	{
		while (str[i] == '*' && str[i + 1] == '*')
			i++;
		if (str[i] == '*')
			wildcard = str_append_chr(wildcard, -1);
		else
			wildcard = str_append_chr(wildcard, str[i]);
		if (wildcard == NULL)
			return (NULL);
		i++;
	}
	return (wildcard);
}
//todo : check double ** in terminal
//adds same str to our wildcard (changes * to -1)

char	**expand_files_current_dir(void)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			**file_names;
	char			*fname;

	file_names = NULL;
	dir = opendir("./");
	if (dir == NULL)
		print_error_errno(NAME, NULL, NULL);
	if (dir == NULL)
		return (NULL);
	dirent = readdir(dir);
	while (dirent)
	{
		fname = ft_strdup(dirent->d_name);
		if (fname == NULL || split_append_str(&file_names, fname) == ERROR)
		{
			free(fname);
			ft_free_split(&file_names);
			return (NULL);
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (file_names);
}
//gets all files from the current dir.

void	expand_wildcard_replace_connected(t_list **l_token,
			t_list *old, t_list *new)
{
	t_list	*prev;
	t_list	*iter;
	t_list	*tmp;

	iter = old;
	prev = lst_node_prev(*l_token, old);
	while (iter && token_content(iter)->flags & TOK_CONNECTED)
	{
		tmp = iter->next;
		lst_node_remove(l_token, iter, c_token_destroy);
		iter = tmp;
	}
	ft_lstlast(new)->next = iter->next;
	lst_node_remove(l_token, iter, c_token_destroy);
	if (prev == old)
		*l_token = new;
	else
		prev->next = new;
}
//deletes connected tokens (for files)
