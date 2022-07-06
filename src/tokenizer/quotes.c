/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:56:01 by fcil              #+#    #+#             */
/*   Updated: 2022/07/06 12:41:22 by fcil             ###   ########.fr       */
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
		token_value  = isclosed(&tcmd, column);
		if(!token_value)
			error_exit("Quote Error");
	}
	*cmd = tcmd;
	return (token_value);
}
