/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:15:52 by fcil              #+#    #+#             */
/*   Updated: 2022/09/01 16:52:52 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_group(t_list *l_cmd, t_list *l_free)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		return (print_error_errno(NAME, NULL, NULL));
	if (pid == 0)
	{
		status = exec_recursive(cmd_content(l_cmd)->l_element, l_free);
		exec_free_all(NULL, l_free);
		exit(status);
	}
	return (exec_wait_pid(pid, NULL));
}

static int	exec_operator_skip(t_list *l_cmd)
{
	if (cmd_content(l_cmd)->type & CMD_AND && exec_exit_status_get() != 0)
		return (1);
	else if (cmd_content(l_cmd)->type & CMD_OR && exec_exit_status_get() == 0)
		return (1);
	else
		return (0);
}

int	exec_recursive(t_list *l_cmd, t_list *l_free)
{
	if (cmd_type(l_cmd) == CMD_SCMD)
		exec_exit_status_set(exec_scmd(l_cmd, l_free));
	else if (cmd_type(l_cmd) == CMD_PIPELINE)
		exec_exit_status_set(exec_pipeline(l_cmd, l_free));
	else if (cmd_type(l_cmd) == CMD_GROUP)
		exec_exit_status_set(exec_group(l_cmd, l_free));
	if (l_cmd->next)
	{
		l_cmd = l_cmd->next;
		while (l_cmd && exec_operator_skip(l_cmd))
			l_cmd = l_cmd->next->next;
		if (l_cmd != NULL)
			exec_exit_status_set(exec_recursive(l_cmd->next, l_free));
	}
	return (exec_exit_status_get());
}

void	exec_free_all(char **argv, t_list *l_free)
{
	if (argv)
		ft_free_split(&argv);
	if (l_free)
		ft_lstclear(&l_free, cmd_destroy);
	if (g_env)
		ft_free_split(&g_env);
	rl_clear_history();
}
