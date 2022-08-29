/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:01:09 by aeser             #+#    #+#             */
/*   Updated: 2022/08/27 17:43:02 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env = NULL;

static char	*get_input(void)
{
	char	*input;
	char	*prompt;

	prompt = env_get_value("PS1");
	if (prompt == NULL)
		prompt = "$> ";
	if (isatty(STDIN_FILENO))
		input = readline(prompt);
	else
		input = get_next_line(STDIN_FILENO);
	if (input == NULL)
		return (NULL);
	else if (input && input[0])
		add_history(input);
	return (input);
}

static void	process_input(char *input)
{
	t_list	*l_token;
	t_list	*l_parser;

	signal(SIGINT, SIG_IGN);
	l_token = NULL;
	l_parser = NULL;
	l_token = lexer(input);
	free(input);
	if (l_token != NULL)
	 	l_parser = parser(l_token);
	// if (l_token != NULL && l_parser != NULL)
	// 	exec_recursive(l_parser, false, l_parser);
	// if (l_parser != NULL)
	// 	ft_lstclear(&l_parser, cmd_destroy);
	// else if (l_token != NULL)
	// 	ft_lstclear(&l_token, c_token_destroy);
}

int	main(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	if (env_init() == ERROR)
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, signal_newline);
		input = get_input();
		process_input(input);
	}
	return (0);
}
