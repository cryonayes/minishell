/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:00:48 by aeser             #+#    #+#             */
/*   Updated: 2022/07/03 16:26:02 by fcil             ###   ########.fr       */
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

char	*isclosed(char **str, char c)
{
	int		i;
	int		j;
	char	*tstr;

	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == c)
		{
			j = -1;
			tstr = malloc(i + 1 * sizeof(char));
			while (++j < i)
			{
				tstr[j] = str[0][j];
			}
			tstr[j] = '\0';
			*str += i;
			return (tstr);
		}
	}
	return (NULL);
}

void	quotes_check(char **cmd, char column)
{
	int		i;
	char	*tcmd;
	char	*token_value;

	tcmd = *cmd;
	i = -1;
	if (*tcmd == column)
	{
		tcmd++;
		token_value  = isclosed(&tcmd, column);
		if(!token_value)
			error_exit("Quote Error"); //quote is not closed.
		printf("|%s|\n", token_value); //todo: create token and add !!!
		//token_create(token_value, get_token_type(token_value), list);
		free(token_value);
	}
	*cmd = tcmd;
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
		printf("STR AFTER SPACE: |%s|\n", tcmd);
		quotes_check(&tcmd, '\'');

		if(*tcmd)
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
