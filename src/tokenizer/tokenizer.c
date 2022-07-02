/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:00:48 by aeser             #+#    #+#             */
/*   Updated: 2022/07/02 17:19:24 by fcil             ###   ########.fr       */
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

char	*isclosed(char *str, char c)
{
	int	i;
	int	j;
	char	*tstr;

	tstr = str;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			j = -1;
			tstr = malloc(i + 1 * sizeof(char));
			while (++j < i)
			{
				printf("%c", str[j]);
			}

			return (tstr);

		}
	}

	return (tstr);
}

t_token	*tokenizer(char *cmd)
{
	t_token	*first;
	int		i;
	int		j;
	bool	isenv;
	char	*tcmd;

	first = tokeni;
	tcmd = cmd;
	isenv = false;
	i = -1;
	while (*tcmd)
	{
		++i;
		if (*tcmd == '"')
		{
			tcmd  = isclosed(&cmd[i + 1], '"');
			printf("%s|\n", tcmd);
			break ;
		}
		tcmd++;
	}
	printf("%d", isenv);
	printf("\n-----END-----\n");
	return (first);
}
