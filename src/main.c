/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:01:09 by aeser             #+#    #+#             */
/*   Updated: 2022/07/02 18:32:58 by fcil             ###   ########.fr       */
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
	//char	*input;

	//while (1)
	//{
	//	input = readline(PROMPT);
	//	if (input == NULL)
	//		continue ;
	//	tokenizer(input);
	//}

	tokenizer("./program arg1\"YEY\"\"\"te\" \" test \"TEST\">file.txt");
	tokenizer("");
}
