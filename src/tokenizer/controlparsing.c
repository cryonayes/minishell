/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlparsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:46:27 by fcil              #+#    #+#             */
/*   Updated: 2022/07/09 00:04:47 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isoperator(char c)
{
	return (ft_isclosebracket(c) || ft_isopeningbracket(c));
}

bool	ft_isclosebracket(char c)
{
	return (c == '<');
}

bool	ft_isopeningbracket(char c)
{
	return (c == '>');
}

bool	ft_isspace(char c)
{
	return (c <= ' ' && c != '\0');
}

bool	ft_isquote(char c)
{
	return (c == '\'' || c == '"');
}
