/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:00:48 by aeser             #+#    #+#             */
/*   Updated: 2022/07/02 16:11:59 by fcil             ###   ########.fr       */
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

//TODO: this function will delete
void	print_keys(char **key)
{
	int i = -1;
	while (key[++i])
	{
		printf("%d: %s\n", i, key[i]);
	}
}

bool	isclosed(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		printf("%c-", str[i]);
		if (str[i] == c)
		{
			return (true);
			break;
		}
	}
	return (false);
}

t_token	*tokenizer(char *cmd)
{
	t_token	*first;
	int		i;
	int		j;
	bool	isenv;
	
	isenv = false;
	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"')
		{
			isenv = isclosed(&cmd[i + 1], '"');
		}	
	}
	printf("%d", isenv);
	return (first);
}
