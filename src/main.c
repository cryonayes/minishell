/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:01:09 by aeser             #+#    #+#             */
/*   Updated: 2022/07/08 20:48:25 by fcil             ###   ########.fr       */
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

void test(t_token **list)
{
	t_token *elem;
	char *value;
	
	value = calloc(2, 1);
	value[0] = '0';
	elem = token_create(value, T_LITERAL);
	token_add(&*list, elem);
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
	char	*cmd;
	list = NULL;
	test(&list);

	while (1)
	{
		cmd = readline("test> ");
		tokenizer(cmd, list);
		print_tokens(list);
		free(cmd);
	}

	destroy_tokens(list);
}
