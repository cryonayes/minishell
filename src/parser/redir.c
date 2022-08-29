/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:44:10 by fcil              #+#    #+#             */
/*   Updated: 2022/08/27 18:44:25 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_type(char *redir)
{
	int	i;

	if (redir == NULL)
		return (ERROR);
	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>' && redir[i + 1] == '\0')
		return (REDIR_OUT);
	else if (redir[i] == '>' && redir[i + 1] == '>')
		return (REDIR_OUT_APP);
	else if (redir[i] == '<' && redir[i + 1] == '\0')
		return (REDIR_IN);
	else if (redir[i] == '<' && redir[i + 1] == '<')
		return (REDIR_HEREDOC);
	else
		return (ERROR);
}
