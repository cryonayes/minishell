/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:01:09 by aeser             #+#    #+#             */
/*   Updated: 2022/07/25 10:39:38 by fcil             ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*list;

	(void)(argc);
	(void)(argv);
	(void)(env);
	list = NULL;
	while (1)
	{
		input = readline(PROMPT);
		printf("%d", *input);
		if (input == NULL)
			continue ;
		tokenizer(input, &list);
		print_tokens(list);
		//destroy_tokens(list); //todo: seg fault will fix
	}
	
}
