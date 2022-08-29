/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:50:48 by fcil              #+#    #+#             */
/*   Updated: 2022/08/26 15:56:00 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(void)
{
	extern char	**environ;
	int			i;

	i = split_count(environ);
	if (i == 0)
		return (0);
	g_env = malloc((i + 1) * sizeof(char *));
	if (g_env == NULL)
		return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
	i = 0;
	while (environ[i])
	{
		g_env[i] = ft_strdup(environ[i]);
		if (g_env[i] == NULL)
		{
			ft_free_split(&g_env);
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
		}
		i++;
	}
	g_env[i] = NULL;
	return (0);
}

char	*env_find_var(char *name)
{
	int	l_name;
	int	i;

	if (name == NULL || g_env == NULL)
		return (NULL);
	if (ft_strchr(name, '='))
		l_name = ft_strchr(name, '=') - name;
	else
		l_name = ft_strlen(name);
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(name, g_env[i], l_name) && g_env[i][l_name] == '=')
			return (g_env[i]);
		i++;
	}
	return (NULL);
}

char	*env_get_value(char *name)
{
	char	*env_var;

	env_var = env_find_var(name);
	if (env_var)
		return (ft_strchr(env_var, '=') + 1);
	else
		return (NULL);
}
