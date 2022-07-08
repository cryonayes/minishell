/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:50:21 by fcil              #+#    #+#             */
/*   Updated: 2022/07/09 00:05:32 by fcil             ###   ########.fr       */
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

void	get_words(char	**cmd, t_token **list)
{
	int		len;
	char	*tcmd;
	char	*value;
	int		i;
	t_token	*n_token;

	tcmd = *cmd;
	len = 0;
	i = -1;
	while (!ft_check_wordend(tcmd[len]))
		len++;
	value = ft_calloc(len + 1, sizeof(char));
	while (!ft_check_wordend(*tcmd))
	{
		value[++i] = *tcmd;
		tcmd++;
	}
	n_token = token_create(value, T_LITERAL);
	token_add(&*list, n_token);
	*cmd = tcmd;
}

void	*tokenizer(char *cmd, t_token **list)
{
	char	*tcmd;

	tcmd = cmd;
	while (*tcmd && ft_isascii(*tcmd))
	{
		if (ft_check_wordend(*tcmd))
		{
			skip_spaces(&tcmd);
			get_operator(&tcmd, list);
			quotes_check(&tcmd, list);
		}
		if (!*tcmd)
			break ;
		get_words(&tcmd, list);
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
