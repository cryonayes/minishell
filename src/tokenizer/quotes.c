/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:56:01 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 18:49:30 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_quotes(char **cmd, char column)
{
	char	*tcmd;
	char	*token_value;

	token_value = NULL;
	tcmd = *cmd;
	if (*tcmd == column)
	{
		tcmd++;
		token_value = isclosed(&tcmd, column);
		if (!token_value)
			error_exit("Quote Error");
	}
	*cmd = tcmd;
	return (token_value);
}

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
