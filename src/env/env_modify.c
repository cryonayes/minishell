/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:39:31 by fcil              #+#    #+#             */
/*   Updated: 2022/09/01 16:41:31 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_unset_var(char *name)
{
	char	*env_var;

	env_var = env_find_var(name);
	if (env_var == NULL)
		return (ERROR);
	split_remove_str(&g_env, env_var);
	return (0);
}

int	env_put_var(char *str)
{
	char	*old_var;
	char	*new_var;
	int		status;

	if (str == NULL || ft_strchr(str, '=') == NULL)
		return (ERROR);
	new_var = ft_strdup(str);
	if (new_var == NULL)
		return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
	old_var = env_find_var(str);
	status = split_replace_str(&g_env, old_var, new_var);
	if (status == ERROR)
	{
		status = split_append_str(&g_env, new_var);
		if (status == ERROR)
			return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
	}
	return (0);
}

int	env_set_env(char *name, char *value)
{
	char	*var_str;
	char	*tmp;
	int		status;

	if (name == NULL || value == NULL)
		return (ERROR);
	tmp = ft_strjoin(name, "=");
	if (tmp == NULL)
		return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
	var_str = ft_strjoin(tmp, value);
	free(tmp);
	if (var_str == NULL)
		return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
	status = env_put_var(var_str);
	free(var_str);
	return (status);
}
