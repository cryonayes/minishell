/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:45:02 by fcil              #+#    #+#             */
/*   Updated: 2022/08/16 15:38:16 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

int	env_init(void)
{
	extern char	**environ;
	int			i;

	i = split_count(environ);
	g_env = malloc((i + 1) * sizeof(char *));
	if (g_env == NULL)
		return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
	i = 0;
	while (environ[i])
	{
		g_env[i] = ft_strdup(environ[i]);
		if (g_env[i] == NULL)
		{
			ft_free_split(&g_env);
			return (print_error(SHELL_NAME, NULL, NULL, strerror(ENOMEM)));
		}
		i++;
	}
	g_env[i] = NULL;
	return (0);
}

char	*env_get_val(char *str)
{
	char	*env_var;

	env_var = env_find_var(str);
	if (env_var)
	{
		return (ft_strchr(env_var, '=') + 1);
	}
	else
		return (NULL);
}

char	*env_find_var(char *str)
{
	int	len;
	int	i;

	if (str == NULL || g_env == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(str, g_env[i], len) && g_env[i][len] == '=')
			return (g_env[i]);
		i++;
	}
	return (NULL);
}
