/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:01:09 by aeser             #+#    #+#             */
/*   Updated: 2022/07/06 13:04:43 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(void)
{
	t_token	*token_lst;
	char	*input;

	while (1)
	{
		token_lst = NULL;
		input = readline(PROMPT);
		if (input && *input)
			add_history(input);
		
	}
}

void test(t_token *list)
{
	t_token *elem;
	char *value;
	
	value = calloc(2, 1);
	value[0] = '0';
	elem = token_create(value, T_LITERAL);
	token_add(&list, elem);

	value = calloc(2, 1);
	value[0] = '1';
	elem = token_create(value, T_LITERAL);
	token_add(&list, elem);

	value = calloc(2, 1);
	value[0] = '2';
	elem = token_create(value, T_LITERAL);
	token_add(&list, elem);

	print_tokens(list);
}

int	main(int argc, char **argv, char **env)
{
	//char	*input;
	(void)(argc);
	(void)(env);
	//while (1)
	//{
	//	input = readline(PROMPT);
	//	if (input == NULL)
	//		continue ;
	//	tokenizer(input);
	//}
	t_token *list;

	list = NULL;
	test(list);
	tokenizer(argv[1], list);
	print_tokens(list);
	destroy_tokens(list);
}
