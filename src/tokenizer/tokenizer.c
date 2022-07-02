/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:00:48 by aeser             #+#    #+#             */
/*   Updated: 2022/07/02 21:04:56 by fcil             ###   ########.fr       */
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

t_token	*tokenizer(char *cmd)
{
	t_token	*first;
	int		i;
	bool	isenv;
	char	*tcmd;
	char	*token_value;

	first = token_init(first);
	tcmd = cmd;
	isenv = false;
	i = -1;
	while (*tcmd)
	{
		if (*tcmd == '"')
		{
			tcmd++;
			token_value  = isclosed(&tcmd, '"');
			if(!token_value)
				error_exit("Quote Error"); //quote is not closed.
			
			printf("|%s|\n", token_value); //todo: create token and add !!!
			free(token_value);
		}
		tcmd++;
	}
	printf("%d", isenv);
	printf("\n-----END-----\n");
	return (first);
}
