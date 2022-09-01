/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 05:22:12 by fcil              #+#    #+#             */
/*   Updated: 2022/08/31 06:14:25 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	pattern_match_file(char *pattern, char **split, char *file)
{
	char	*shift_fname;
	int		i;

	shift_fname = file;
	i = 0;
	while (split[i])
	{
		shift_fname = ft_strnstr(shift_fname, split[i], ft_strlen(shift_fname));
		if (shift_fname == NULL)
			return (0);
		shift_fname += ft_strlen(split[i]); //skips nulls
		i++;
	}
	if (pattern[0] != -1
		&& ft_strncmp(file, split[0], ft_strlen(split[0])) != 0)
		return (0);
	if (pattern[ft_strlen(pattern) - 1] != -1
		&& ft_strncmp(file + ft_strlen(file) - ft_strlen(split[i - 1]),
			split[i - 1], ft_strlen(split[i - 1]) + 1) != 0)
		return (0);
	if (pattern[0] != '.' && file[0] == '.')
		return (0);
	return (1);
}
//(checks * with -1)
//if files pair of our token returns 1

static t_list	*expand_pattern_to_list(char *pattern, char **split,
					char **files)
{
	t_list	*l_wildcard;
	t_list	*new_token;
	char	*tmp;
	int		i;

	l_wildcard = NULL;
	i = 0;
	while (files[i])
	{
		if (pattern_match_file(pattern, split, files[i]))
		{
			tmp = ft_strdup(files[i]);
			printf("%s\n", tmp);
			new_token = token_create(tmp, TOK_WILDCARD);
			if (tmp == NULL || new_token == NULL)
			{
				ft_lstdelone(new_token, c_token_destroy);
				ft_lstclear(&l_wildcard, c_token_destroy);
				return (NULL);
			}
			ft_lstadd_back(&l_wildcard, new_token);
		}
		i++;
	}
	return (l_wildcard);
}
//gets paired file in files[i]
//and adds the token as TOK_WILDCARD

static int	expand_wildcard_token(t_list *token, t_list **l_wildcard,
				char **files)
{
	t_list	*iter;
	char	**split;
	char	*pattern;

	pattern = expand_pattern_get(token);
	split = ft_split(pattern, -1);
	if (pattern == NULL || split == NULL)
	{
		free(pattern);
		if (split != NULL)
			ft_free_split(&split);
		return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
	}
	*l_wildcard = expand_pattern_to_list(pattern, split, files);
	iter = *l_wildcard;
	while (iter)
	{
		token_content(iter)->flags = token_content(token)->flags;
		token_content(iter)->flags &= ~(TOK_CONNECTED);
		token_content(iter)->flags &= ~(TOK_D_QUOTE | TOK_S_QUOTE);
		iter = iter->next;
	}
	free(pattern);
	ft_free_split(&split);
	return (0);
}
//splits our pattern(str) with -1 
//we changed * to -1 in the expand_pattern_get
//after the (expand_pattern_to_list) function, it deletes old tokens

int	expand_wildcard_list(t_list	**l_token, char **files)
{
	t_list	*l_wildcard;
	t_list	*iter;
	t_list	*tmp;

	iter = *l_token;
	while (iter)
	{
		l_wildcard = NULL;
		tmp = iter;
		while (token_content(tmp)->flags & TOK_CONNECTED)
			tmp = tmp->next;
		tmp = tmp->next;
		if (expand_token_is_wildcard(iter))
		{
			if (expand_wildcard_token(iter, &l_wildcard, files) == ERROR)
				return (ERROR);
			if (l_wildcard != NULL)
				expand_wildcard_replace_connected(l_token, iter, l_wildcard);
		}
		iter = tmp;
	}
	return (0);
}
//firsty checks is it wildcard or not.
//gets paired file names and adds it the token in expand_wildcard_token
