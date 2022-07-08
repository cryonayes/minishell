/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 20:26:27 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 22:59:32 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operatorlen(char *str)
{
	int	len;

	len = 0;
	while (ft_isoperator(str[len]))
		len++;
	return (len);
}

int	get_valueofoperator(char **value, char **cmd)
{
	char	*tcmd;
	int		(*func)(char);
	int		i;

	i = 0;
	tcmd = *cmd;
	func = ft_isopeningbracket;
	if (ft_isclosebracket(*tcmd))
		func = ft_isclosebracket;
	while (func(*tcmd))
	{
		value[0][i] = *tcmd;
		tcmd++;
		i++;
	}
	*cmd = tcmd;
	return (i);
}

t_tokenType	get_operatortype(char *value)
{
	if (!ft_strncmp(value, "<<", 2))
		return (T_HEREDOC);
	return (T_REDIRECT);
}

void	get_operator(char **cmd, t_token **list)
{
	char	*value;
	char	*tcmd;
	int		len;
	int		i;
	t_token	*n_token;

	tcmd = *cmd;
	len = get_operatorlen(tcmd);
	if (len == 0)
		return ;
	if (len > 2)
		error_exit("you cant use more than 2 bracket");
	value = ft_calloc(len + 1, sizeof(char));
	i = get_valueofoperator(&value, &tcmd);
	printf("%d %d %s %s", i, len, *cmd, value);
	if (i != len)
		error_exit("WTF ARE YOU DOING \n use these; '<<, >>, <, >'");
	n_token = token_create(value, get_operatortype(value));
	token_add(&*list, n_token);
	*cmd = tcmd;
}
