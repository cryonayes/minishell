/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:26:50 by fcil              #+#    #+#             */
/*   Updated: 2022/07/08 16:43:15 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char	*str)
{
	printf("OH NO BEST SHELL HAS DOWN!!!\n Error Message: ");
	printf("%s\n", str);
	exit(-1);
}

char	*ft_sum_strjoin(char *src, char *str2)
{
	char	*m_str;

	m_str = src;
	m_str = ft_strjoin(m_str, str2);
	if (!m_str)
		return (src);
	free(src);
	return (m_str);
}
