/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:32:29 by fcil              #+#    #+#             */
/*   Updated: 2022/09/01 16:47:21 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(int argc __attribute((unused)), char **argv)
{
	int		i;
	int		newline;

	newline = 0;
	i = 1;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		i++;
	if (i == 1)
		newline = 1;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	builtin_pwd(int argc __attribute((unused)),
	char **argv __attribute((unused)))
{
	char	buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)))
	{
		ft_putendl_fd(buf, STDOUT_FILENO);
		return (0);
	}
	else
	{
		print_error_errno(NAME, "pwd", NULL);
		return (EXIT_FAILURE);
	}
}

int	builtin_env(int argc __attribute((unused)),
	char **argv __attribute((unused)))
{
	int	i;

	if (g_env == NULL)
	{
		print_e(NAME, "env", NULL, "environ not set");
		return (EXIT_FAILURE);
	}
	i = 0;
	while (g_env[i])
	{
		ft_putendl_fd(g_env[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	builtin_unset(int argc __attribute((unused)), char **argv)
{
	int	status;
	int	i;
	int	j;

	status = 0;
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] && env_is_var_char(argv[i][j]))
			j++;
		if (argv[i][j] != '\0' || argv[i][0] == '\0')
		{
			print_e(NAME, "unset", argv[i], "not a valid identifier");
			status = EXIT_FAILURE;
		}
		else
			env_unset_var(argv[i]);
		i++;
	}
	return (status);
}