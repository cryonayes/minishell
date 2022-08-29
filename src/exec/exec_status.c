/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:29:22 by fcil              #+#    #+#             */
/*   Updated: 2022/08/26 16:36:24 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*exit_status_pointer(void)
{
	static int	last_exit_status = 0;

	return (&last_exit_status);
}
//creates a static variable which can be access by other functions
//to store the exit code of the last running command

void	exec_exit_status_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*exit_status_pointer() = status;
}

int	exec_exit_status_get(void)
{
	return (*exit_status_pointer());
}
