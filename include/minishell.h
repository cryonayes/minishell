/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:07:30 by fcil              #+#    #+#             */
/*   Updated: 2022/08/29 17:18:55 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# include "signal.h"
# include "libft.h"
# include "errno.h"
# include <readline/readline.h>
# include <readline/history.h>

# define ERROR		-1
# define NAME	"minishell"

extern char	**g_env;

//env.c
int			env_init(void);
char		*env_find_var(char *name);
char		*env_get_value(char *name);

//get_next_line.c
char		*get_next_line(int fd);
char		*str_append_chr(char *str, char append);
char		*str_append_str(char *str, char *append);

//utils.c
int			split_count(char **argv);
int			print_e(char *s1, char *s2, char *s3, char *message);
void		ft_free_split(char ***split);
int			print_error_errno(char *s1, char *s2, char *s3);

//ft_lstactions.c
int			lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));
t_list		*lst_node_prev(t_list *lst, t_list *node);
int			lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end);

//signal.c
void		signal_newline(int sig);
void		signal_default(int sig);

//-----TOKENS-----
# define TOK_TEXT			1
# define TOK_S_QUOTE		2
# define TOK_D_QUOTE		4
# define TOK_REDIR_FILE		8
# define TOK_CONNECTED		16
# define TOK_BIN_OP			32
# define TOK_PIPE			64
# define TOK_O_BRACKET		128
# define TOK_C_BRACKET		256
# define TOK_REDIR			512
# define TOK_HEREDOC		1024
# define TOK_WILDCARD		2048


typedef struct s_token_content
{
	int		flags;
	char	*str;
}	t_c_token;

//tokens.c
t_list		*token_create(char *string, int type);
t_c_token	*token_content(t_list *token);
void		c_token_destroy(void *c_token);
int			token_is_cmd(t_list *token);
char		*token_to_str(t_list *l_token);

//-----LEXER------
# define WHITESPACES		" \t\n"

//lexer.c
t_list		*lexer(char *input);

//lexer_op.c
int			lexer_logic_op(char *str, int *i, t_list **l_token);
int			lexer_pipe_op(char *str, int *i, t_list **l_token);
int			lexer_parentheses_op(char *str, int *i, t_list **l_token);
int			lexer_redir_op(char *str, int *i, t_list **l_token);
//lexer_op_text.c
int			lexer_text_op(char *str, int *i, t_list **l_token);
int			lexer_quote_op(char *str, int *i, t_list **l_token);
int			lexer_syntax_check(t_list *l_token);
//lexer_syntax.c
int			syntax_bin_op(t_list *l_token);
int			syntax_pipe(t_list *l_token);
int			syntax_brackets(t_list *l_token);
int			syntax_missing_op(t_list *l_token);
int			syntax_redir(t_list *l_token);

//-----EXEC-------
//exec_status.c
void		exec_exit_status_set(int status);
int			exec_exit_status_get(void);

//-----PARSER-----
//parser.c
t_list		*parser(t_list *l_token);

//parser_group.c
int			parser_cmd_group_merge(t_list **l_cmd);

//parser_pipeline.c
int			parser_cmd_pipeline_merge(t_list **l_cmd);

//-----CMD------
# define CMD_SCMD		1
# define CMD_AND		2
# define CMD_OR			4
# define CMD_PIPE		8
# define CMD_O_BRACKET	16
# define CMD_C_BRACKET	32
# define CMD_PIPELINE	64
# define CMD_GROUP		128
# define CMD_L_SCMD		256
# define CMD_L_CMD		512

typedef struct s_scmd_content
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}	t_scmd;

typedef struct s_cmd_content
{
	int		type;
	t_list	*l_element;
}	t_cmd;

//commands.c
t_list		*cmd_create(int type);
t_cmd		*cmd_content(t_list *cmd);
void		cmd_destroy(void *cmd);
int			cmd_type(t_list *cmd);
int			cmd_type_from_token(t_list *token);

//simple_commands.c
t_list		*scmd_create(int type);
t_scmd		*scmd_content(t_list *element);
void		scmd_destroy(void *c_element);

//------REDIR------
# define REDIR_OUT		1
# define REDIR_OUT_APP	2
# define REDIR_IN		3
# define REDIR_HEREDOC	4

//redir.c
int			redir_type(char *redir);

// PRINTER_CMD
void	printer_cmd(t_list *l_cmd);
void	printer_structure(t_list *l_cmd);
void	print_tokens(t_list	*l_token);

// PRINTER_SCMD
void	printer_scmd(t_scmd *scmd);
void	printer_other(int type);
void	printer_scmd_pipeline(t_list *l_scmd_pipeline, int newline);


#endif
