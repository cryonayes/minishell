/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 23:04:05 by fcil              #+#    #+#             */
/*   Updated: 2022/09/01 16:34:21 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const struct s_builtins	g_builtins[] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"env", builtin_env},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{NULL, NULL},
};

static int	num_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
	{
		print_e(NAME, "exit", str, "numeric argument required");
		return (0);
	}
	else if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			print_e(NAME, "exit", str, "numeric argument required");
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_exit(int argc, char **argv, t_list *l_free)
{
	int	exit_num;

	if (isatty(STDERR_FILENO))
		ft_putstr_fd("exit\n", STDERR_FILENO);
	exit_num = exec_exit_status_get();
	if (argc >= 2 && num_is_numeric(argv[1]) == 0)
		exit_num = 255;
	else if (argc == 2)
		exit_num = ft_atoi(argv[1]);
	else if (argc > 2)
	{
		print_e(NAME, "exit", NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	exec_free_all(argv, l_free);
	exit(exit_num);
}

int	builtin_check(char **argv)
{
	int	c_name;
	int	i;

	i = 0;
	if (argv[0] && !ft_strncmp(argv[0], "exit", 5))
		return (INT_MAX);
	while (g_builtins[i].name != NULL && argv)
	{
		c_name = ft_strlen(g_builtins[i].name);
		if (argv[0] && !ft_strncmp(argv[0], g_builtins[i].name, c_name + 1))
			return (i + 1);
		i++;
	}
	return (0);
}

int	builtin_exec(char **argv, t_list *l_free)
{
	int	i_builtin;

	i_builtin = builtin_check(argv);
	if (i_builtin == 0)
		return (ERROR);
	errno = 0;
	if (i_builtin == INT_MAX)
		return (builtin_exit(split_count(argv), argv, l_free));
	return (g_builtins[i_builtin - 1].func(split_count(argv), argv));
}
