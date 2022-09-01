/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:29:51 by fcil              #+#    #+#             */
/*   Updated: 2022/08/31 06:15:15 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_var(t_scmd *scmd)
{
	int		status;

	status = expand_var_token_list(scmd->l_argv);
	if (status != ERROR)
		status = expand_var_token_list(scmd->l_redir);
	if (status != ERROR)
		status = expand_var_splitting(&(scmd->l_argv));
	if (status != ERROR)
		status = expand_var_splitting(&(scmd->l_redir));
	return (status);
}

int	expand_wildcard(t_scmd *c_scmd)
{
	char	**files;
	int		status;

	files = expand_files_current_dir();
	if (files == NULL)
		return (print_e(NAME, NULL, NULL, strerror(ENOMEM)));
	status = expand_wildcard_list(&(c_scmd->l_argv), files);
	if (status != ERROR)
		status = expand_wildcard_list(&(c_scmd->l_redir), files);
	ft_free_split(&files);
	return (status);
}
//gets files 
//and add them instead for our file_names token
