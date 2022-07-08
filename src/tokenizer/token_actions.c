/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:19:44 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 23:48:13 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add(t_token **first, t_token *node)
{
	t_token	*last;

	if (!node->value)
		return ;
	if (*first == NULL)
	{
		*first = node;
		return ;
	}
	last = *first;
	while (last->next)
		last = last->next;
	last->next = node;
	node->previous = last;
	node->next = NULL;
}

t_token	*token_create(char *value, enum e_tokenType type)
{
	t_token	*n_token;

	if (!value)
		return (NULL);
	n_token = ft_calloc(1, sizeof(t_token));
	n_token->type = type;
	n_token->value = value;
	n_token->next = NULL;
	n_token->previous = NULL;
	return (n_token);
}

void	print_tokens(t_token *first)
{
	int		i;
	t_token	*t;

	printf("\nTOKENS;\n");
	i = 0;
	t = first;
	while (t != NULL)
	{
		printf("id: %d Value : %s, Token : %d\n", i, t->value, t->type);
		t = t->next;
		i++;
	}
}

void	destroy_tokens(t_token *first)
{
	t_token	*t;

	if (!first)
		return ;
	t = first;
	while (t != NULL)
	{
		free(t->value);
		first = t;
		t = first->next;
		free(first);
	}
	printf("deleted all nodes\n");
}
