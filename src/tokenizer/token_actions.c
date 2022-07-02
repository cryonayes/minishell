/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:19:44 by fcil              #+#    #+#             */
/*   Updated: 2022/07/02 18:22:22 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*token_init(t_token *stack)
{
	stack->type = 0;
	stack->value = "";
	stack->next = NULL;
	stack->previous = NULL;
	return (stack);
}

void		token_add(t_token *first, t_token *node)
{
	t_token	*last;
	
	last = first;
	while (last->next)
		last = last->next;
	last->next = node;
	node->previous = last;
	node->next = NULL;
}

void		token_create(char *value, enum e_tokenType type, t_token *first)
{
	t_token	*n_token;

	n_token = malloc(sizeof(t_token));
	n_token->type = type;
	n_token->value = value;
	token_add(first, n_token);
}
