/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:01:09 by aeser             #+#    #+#             */
/*   Updated: 2022/08/16 15:51:32 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_loop(void)
{
	t_token	*token_lst;
	char	*input;

	while (1)
	{
		token_lst = NULL;
		input = readline(PROMPT);
		if (input && *input)
			add_history(input);
	}
}

void	printdir(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("\nDir: %s", cwd);
}

int	takeinput(char **str)
{
	prompt = env_get_val("PS1");
	if (prompt == NULL)
		prompt = PROMPT;
	*str = readline(PROMPT);
	if (ft_strlen(*str) != 0)
	{
		add_history(*str);
		return (0);
	}
	return (1);
}

void execArgs(t_token *list)
{
	pid_t pid = fork(); 
	t_token	*cur;
	char	**args;

	cur = list;
	args[0] = ft_strjoin(BINPATH, cur->value);
	cur = cur->next;
	args[1] = cur->value;
	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if (pid == 0) {
		printf("log:|%s|\nlog:|%s|\n", args[0], args[1]);
		execve(args[0], args[1], NULL);
		exit(0);
	} else {
		wait(NULL); 
		return;
	}
}

int	main(void)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	if (env_init() == ERROR)
		return (EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, signalint_func);
		if (takeinput(&input))
			continue ;

		// tokenizer(input, &list);
		// print_tokens(list);
		// execArgs(list);
		// //destroy_tokens(list); //todo: seg fault will fix
	}

}
