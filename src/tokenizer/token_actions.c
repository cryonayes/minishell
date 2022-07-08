/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:19:44 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 16:46:04 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		token_add(t_token **first, t_token *node)
{
	t_token	*last;
	
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

t_token		*token_create(char *value, enum e_tokenType type)
{
	t_token	*n_token;

	n_token = malloc(sizeof(t_token));
	n_token->type = type;
	n_token->value = value;
	return (n_token);
}

void	print_tokens(t_token *first)
{
	int		i;
	t_token *t;

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
	t_token *t;

	t = first;
	while (t != NULL)
	{
		free(t->value);
		free(t);
		t = t->next;
	}
}