/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:50:21 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 17:10:07 by fcil             ###   ########.fr       */
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

char	*get_envkey(char **ptr)
{
	char	*str;
	char	*key;
	int		i;

	i = 0;
	key = *ptr;
	while (isalnum(key[i]) && key[i])
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	*ptr = &key[i];
	while (--i >= 0)
		str[i] = key[i];
	return (str);
}

char	*getkeys_dquote(char	*value)
{
	char	**keys;
	int		i;
	char	*n_value;
	char	*key_ptr;

	keys = ft_split(value, '$');
	n_value = ft_calloc(1, 1);
	i = 0;
	if (value[0] == '$')
		i = -1;
	else
	{
		n_value = ft_sum_strjoin(n_value, keys[0]);
		free(keys[0]);
	}
	while (keys[++i])
	{
		key_ptr = keys[i];
		n_value = ft_sum_strjoin(n_value, getenv(get_envkey(&key_ptr)));
		n_value = ft_sum_strjoin(n_value, key_ptr);
		free(keys[i]);
	}
	free(keys);
	free(value);
	return (n_value);
}	

void	quotes_check(char **cmd, t_token **list)
{
	t_token	*n_token;
	char	*value;

	n_token = NULL;
	value = get_quotes(cmd, '"');
	if (value != NULL)
	{
		value = getkeys_dquote(value);
		n_token = token_create(value, T_LITERAL);
		token_add(&*list, n_token);
		value = NULL;
	}
	value = get_quotes(cmd, '\'');
	if (value != NULL)
	{
		n_token = token_create(value, T_LITERAL);
		token_add(&*list, n_token);
	}
}

void	skip_spaces(char **cmd)
{
	char	*tcmd;

	tcmd = *cmd;
	while (*tcmd <= ' ' && *tcmd != '\0')
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
		skip_spaces(&tcmd);
		quotes_check(&tcmd, &list);
		if (*tcmd)
			tcmd++;
		//printf("STR AFTER : |%s|\n", tcmd);
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
