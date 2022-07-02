/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 17:19:44 by fcil              #+#    #+#             */
/*   Updated: 2022/07/02 17:47:25 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token		*token_init(t_token *stack)
{
	stack->type = 0;
	stack->value = "";
	stack->next = NULL;
	stack->previous = NULL;
}

// void	token_add(t_token *stack, char *node)
// {
// 	node->prev = stack->first->prev;
// 	node->prev->next = node;
// 	node->next = stack->first;
// 	stack->first->prev = node;
	
// 	return (node);
// }
