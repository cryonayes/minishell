/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 18:26:50 by fcil              #+#    #+#             */
/*   Updated: 2022/07/02 18:28:38 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char	*str)
{
	printf("OH NO BEST SHELL HAS DOWN!!!\n Error Message: ");
	printf("%s\n", str);
	exit(-1);
}