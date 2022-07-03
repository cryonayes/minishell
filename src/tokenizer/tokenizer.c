/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:50:21 by fcil              #+#    #+#             */
/*   Updated: 2022/07/03 17:14:47 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

/*
./program arg1 "arg2">file.txt
	./program arg1 arg2 > file.txt

echo ~/file.txt
	echo /home/user/file.txt

echo "'$USER'"
	'aeser'

echo "$USER"
	aeser

echo '$USER'
	$USER

1) Operatörlerden önce ve sonra boşluk koyulacak
2) Eğer çift tırnak içerisinde ise:
	1. ~ => $HOME ile değiştirilecek
	2. 
*/


void	quotes_check(char **cmd, t_token **list)
{
	t_token n_token;
	char	*value;

	value = get_quotes(cmd, '\'');
	if (value != NULL)
	{
		//n_token = token_create(value, T_LITERAL, *list);
	}
	
	get_quotes(cmd, '"');
}

void	skip_spaces(char **cmd)
{
	char	*tcmd;

	tcmd = *cmd;
	while (*tcmd <= ' ' && *tcmd > 0)
	{
		printf("c:%d\n",*tcmd);
		tcmd++;
	}
	*cmd = tcmd;
}

void	*tokenizer(char *cmd, t_token *list)
{
	int		i;
	char	*tcmd;

	
	tcmd = cmd;
	i = -1;
	while (*tcmd)
	{
		skip_spaces(&tcmd);
		quotes_check(&tcmd, &list);
		if (*tcmd)
			tcmd++;
		printf("STR AFTER : |%s|\n", tcmd);
	}
	printf("\n-----END-----\n");
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
