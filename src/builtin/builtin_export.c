/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:37:40 by fcil              #+#    #+#             */
/*   Updated: 2022/09/01 16:45:53 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_vars(void)
{
	char	**env_copy;
	int		l_var_name;
	int		i;

	if (g_env == NULL || *g_env == NULL)
		return ;
	env_copy = malloc((split_count(g_env) + 1) * sizeof(char *));
	if (env_copy == NULL)
	{
		print_e(NAME, NULL, NULL, strerror(ENOMEM));
		return ;
	}
	env_copy = ft_memcpy(env_copy, g_env,
			(split_count(g_env) + 1) * sizeof(char *));
	split_sort(env_copy);
	i = 0;
	while (env_copy[i])
	{
		l_var_name = ft_strchr(env_copy[i], '=') - env_copy[i];
		printf("%.*s", l_var_name + 1, env_copy[i]);
		printf("\"%s\"\n", env_get_value(env_copy[i]));
		i++;
	}
	free(env_copy);
}

static int	is_valid_argument(char *arg)
{
	int	i;

	if (arg[0] == '\0' || arg[0] == '=')
		return (0);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=' && env_is_var_char(arg[i]))
		i++;
	if (arg[i] == '\0' || arg[i] == '=')
		return (1);
	else
		return (0);
}

int	builtin_export(int argc, char **argv)
{
	int	status;
	int	i;

	status = EXIT_SUCCESS;
	if (argc == 1)
		print_vars();
	i = 1;
	while (argc > 1 && argv[i])
	{
		if (is_valid_argument(argv[i]) == 0)
		{
			print_e(NAME, argv[i], NULL, "not a valid identifier");
			status = EXIT_FAILURE;
		}
		else if (ft_strchr(argv[i], '='))
			env_put_var(argv[i]);
		i++;
	}
	return (status);
}
