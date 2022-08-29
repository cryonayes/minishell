/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:52:01 by fcil              #+#    #+#             */
/*   Updated: 2022/08/27 19:17:30 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

int	print_e(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (ERROR);
}

int	print_error_errno(char *s1, char *s2, char *s3)
{
	print_e(s1, s2, s3, strerror(errno));
	errno = 0;
	return (ERROR);
}

void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	while ((*split)[i] != NULL)
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}
