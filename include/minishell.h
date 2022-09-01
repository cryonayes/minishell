/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 17:07:30 by fcil              #+#    #+#             */
/*   Updated: 2022/09/01 19:34:48 by fcil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "signal.h"
# include "libft.h"
# include "errno.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <limits.h>
# include "fcntl.h"
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>

# define ERROR		-1
# define NAME	"minishell"

extern char	**g_env;

//env.c
int			env_init(void);
char		*env_find_var(char *name);
char		*env_get_value(char *name);
int			env_is_var_char(char c);
//env_modify.c
int			env_set_env(char *name, char *value);
int			env_put_var(char *str);
int			env_unset_var(char *name);
//get_next_line.c
char		*get_next_line(int fd);
char		*str_append_chr(char *str, char append);
char		*str_append_str(char *str, char *append);
char		str_last_chr(char *str);

//utils.c
int			print_e(char *s1, char *s2, char *s3, char *message);
void		ft_free_split(char ***split);
int			print_error_errno(char *s1, char *s2, char *s3);

// utils_split.c
int			split_count(char **argv);
int			split_append_str(char ***split, char *str);
int			split_remove_str(char ***split, char *remove_str);
int			split_replace_str(char ***split, char *old_str, char *new_str);
void		split_sort(char **split);

//ft_lstactions.c
int			lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));
t_list		*lst_node_prev(t_list *lst, t_list *node);
int			lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end);

//signal.c
void		signal_newline(int sig);
void		signal_default(int sig);
int			termios_change(int control);

//tokenlist.c
char		**l_token_to_split(t_list *l_token);

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
// POSIX BASED EXIT STATUS
# define EXEC_NOEXEC	126
# define EXEC_NOTFOUND	127
//exec_status.c
void		exec_exit_status_set(int status);
int			exec_exit_status_get(void);
//exec.c
int			exec_recursive(t_list *l_cmd, t_list *l_free);
void		exec_free_all(char **argv, t_list *l_free);
//exec_scmd.c
int			exec_scmd(t_list *scmd, t_list *l_free);
int			exec_scmd_preperation(t_list *scmd, char ***argv);
int			exec_scmd_exec(char **argv);
//exec_waitpid.c
int			exec_wait_pid(int last_pid, char *name);
int			exec_wait_for_all(int last_pid);
//exec_scmd_path.c
int			exec_scmd_search_path(char **argv);
void		exec_scmd_free_exit(int status, char **argv, t_list *l_free);

//exec_pipeline.c
int			exec_pipeline(t_list *pipeline, t_list *l_free);

//exec_pipeline_pipes.c
void		exec_pipeline_pipes_close(int pipes[2][2], int i, int last);
void		exec_pipeline_pipes_set(int fd[2], int pipes[2][2], int i,
				int last);

//-----PARSER-----
//parser.c
t_list		*parser(t_list *l_token);
//parser_group.c
int			parser_cmd_group_merge(t_list **l_cmd);
//parser_pipeline.c
int			parser_cmd_pipeline_merge(t_list **l_cmd);
//parser_heredoc.c
int			parser_heredoc(t_list *l_token);

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

typedef struct s_redir_undo_content
{
	int		fd_repl;
	int		fd_repl_dup;
}	t_redir_undo;

//redir.c
int			redir_type(char *redir);
int			redir(t_list *l_token, t_list **l_undo);

//redirundo.c
int			redir_undo_add_fd(t_list **l_undo, int fd);
int			redir_undo(t_list **l_undo);

//-----EXPAND------
//expand.c
int			expand_var(t_scmd *scmd);
int			expand_wildcard(t_scmd *c_scmd);

//expand_var_token.c
int			expand_var_token_list(t_list *l_token);

//expand_var_split.c
int			expand_var_splitting(t_list **l_token);

//expand_wildcard
int			expand_wildcard_list(t_list	**l_token, char **files);
//expand_wildcard_utils.c
int			expand_token_is_wildcard(t_list *token);
char		*expand_pattern_get(t_list *token);
char		*expand_wildcard_append_str(char *wildcard, t_list *token);
char		**expand_files_current_dir(void);
void		expand_wildcard_replace_connected(t_list **l_token, t_list *old,
				t_list *new);

//-----BUILTINS-----
struct s_builtins
{
	char	*name;
	int		(*func)(int argc, char **argv);
};

// builtin.c
int			builtin_check(char **argv);
int			builtin_exec(char **argv, t_list *l_free);
int			builtin_exit(int argc, char **argv, t_list *l_free);

int			builtin_cd(int argc, char **argv);
int			builtin_export(int argc, char **argv);

//builtin_func.c
int			builtin_echo(int argc, char **argv);
int			builtin_env(int argc, char **argv);
int			builtin_pwd(int argc, char **argv);
int			builtin_unset(int argc, char **argv);

#endif
