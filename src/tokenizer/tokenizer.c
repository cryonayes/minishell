/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:50:21 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 20:26:56 by fcil             ###   ########.fr       */
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

bool	ft_check_wordend(char c)
{
	return (ft_isspace(c) || ft_isquote(c) || ft_isoperator(c) || c == '\0');
}

void	skip_spaces(char **cmd)
{
	char	*tcmd;

	tcmd = *cmd;
	while (ft_isspace(*tcmd))
		tcmd++;
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
		if (ft_check_wordend(*tcmd))
		{
			skip_spaces(&tcmd);
			get_operator(&tcmd, &list);
			quotes_check(&tcmd, &list);
		}
		//todo: Get str val. and add list.
		if (*tcmd)
			tcmd++;
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
