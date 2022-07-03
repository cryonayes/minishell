/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeser <aeser@42kocaeli.com.tr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:01:09 by aeser             #+#    #+#             */
/*   Updated: 2022/07/03 14:49:07 by aeser            ###   ########.fr       */
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
	t_token list;
	tokenizer(argv[1], &list);
}

/*
	./command "$HOME">file.txt
		./command "$HOME" > file.txt
		[./command] ["$HOME"] [>] [file.txt]
		[./command] ["/home/aeser"] [>] [file.txt]
		
		[./command] -> {t_type: T_Literal, value: "./command", prev: NULL, next..}
		["/home/aeser"] -> {t_type: T_Literal, value: "/home/aeser", prev: &["./command"], next..}
		[>,>>, <] -> {t_type: T_Redirect, value: ">", prev: &["/home/aeser"], next..}
		[file.txt] -> {t_type: T_File, value: "file.txt", prev: &[">"], next..}
		[<<] -> {t_type: T_Heredoc, value: "<<", prev: &["file.txt"], next..}

	echo '"$HOME"' "'$HOME'">>test.txt
*/
