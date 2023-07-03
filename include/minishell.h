/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:58:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/03 16:36:44 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

/////////////////////////// ENVIRONMENT //////////////////////////////////
typedef struct s_data_env
{
	int		size;
	char	**envp;
	int		stdin;
	int		stdout;
}	t_data_env;

/////////////////////////////// PARSING //////////////////////////////////
//////////////////////////////////////////////////////////////////////////
typedef struct s_token //liste doublement chainée contenant deux variables
{
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
	char			type;
	char			join_prev;
	char			join_next;
}	t_token;

typedef struct s_lexing
{
	t_token	*tklist_head;
	char	*input;
	int		tklist_size;
}	t_lexing;

// define.c
int				define_redirs(t_lexing *ltable);
void			define_delims(t_lexing *ltable);
int				define_files(t_lexing *ltable);

// define2.c
void			define_args(t_lexing *ltable);
int				merge_flags(t_lexing *ltable);
void			check_access(t_token *token, t_data_env *data_env);
int				define_cmds(t_lexing *ltable, t_data_env *data_env);

// define3.c
int				check_builtins(t_token *token);
int				check_path(char **envp);
char			*find_cmd_path(char	*cmd_name, char **envp);

// expand.c
int				update_token_content(t_token *token, char *variable);
int				expand_token(
					t_token *token, t_lexing *ltable, t_data_env *data_env);
char			*clean_up_quotes(
					char *oldcontent, t_lexing *ltable, t_data_env *data_env);
int				format_tokens(t_lexing *ltable, t_data_env *data_env);
int				expand_token_list(t_lexing *ltable, t_data_env *data_env);

//expand2.c
char			*extract_variable_value(char **env);
char			*fetch_oldcontent_end(char *oldcontent);
int				check_token_end(t_token *token);
int				update_content_full(t_token *token, char *variable);
int				update_content_partial(t_token *token, char *variable);


// lexing.c
int				create_redir_token(
					t_lexing *ltable, t_data_env *data_env, int *reader);
int				find_quote_len(t_lexing *ltable, int reader, char quote_char);
int				create_quoted_token(
					t_lexing *ltable, t_data_env *data_env, int *reader);
int				create_regular_token(
					t_lexing *ltable, t_data_env *data_env, int *reader);
int				create_token_list(t_lexing *ltable, t_data_env *data_env);

//lexing2.c
void			define_joins(t_lexing *ltable, t_token *quoted, int reader, int quote_len);

// parsing.c
char			last_char(char *str);
int				parse_token_list(t_lexing *ltable, t_data_env *data_env);
int				parse_redirections(t_lexing *ltable, t_data_env *data_env);
int				join_quotes(t_lexing *ltable, t_data_env *data_env);

// quit.c
int				free_array(char **arr);
int				free_structs(t_lexing *ltable,
					t_data_env *data_env, char *error_msg, char mode);

// temp.c
void			print_token_list(t_token **head);
void			rev_print_token_list(t_token **last, t_token **head);

// tokens.c
t_token			*tk_new(char *content);
int				tk_size(t_token *token);
t_token			*tk_last(t_token *token);
void			tk_delone(t_token *token);
void			tk_clear(t_token **head);

// tokens2.c

void			tk_add_back(t_token **head, t_token *new);
void			tk_addto(t_token **head, t_token *new, int pos);
void			tk_moveto(t_token **head, t_token *token, int pos);
t_token			*tk_delone_and_link(t_token **head, t_token *token);

//tokens3.c
t_token			*tk_merge(t_token **head, t_token *token1, t_token *token2);
t_token			*tk_merge_quote(t_token **head, t_token *token1, t_token *token2);

/////////////////////////////// EXECUTION ////////////////////////////////
//////////////////////////////////////////////////////////////////////////
typedef struct s_cmd
{
	int		argc;
	char	**argv;
	int		pipe;
	int		pipefd[2];
	int		final_cmd;
	int		fd_in;
	int		fd_out;
	int		pid;
	char	*cmd_path;
	int		final_pid;
	int		has_cmd;
	char	*first_arg;
	int		first_arg_done;
	int		fd_heredoc;
}				t_cmd;

// ft_close.c
void			ft_close(int *fd);
void			ft_close_all_fds(void);

// ft_error_exec.c
void			ft_error_no_such_file(char *file);
void			ft_error_cmd_not_found(char *cmd);
void			ft_error(int status);

// ft_execute_bis.c
void			ft_std_backup(t_data_env *data_env);
void			ft_set_stdin_to_null(int builtin_done);
int				ft_init_pipe_before(t_cmd *cmd);
void			ft_restore_before_next_prompt(t_data_env *data_env, t_cmd *cmd);

// ft_execute.ter
void			ft_exec_cd_utils(t_cmd *cmd, t_data_env *data_env);
int				ft_exec_cd(int pipe_before, t_cmd *cmd, t_data_env *data_env);
int				ft_exec_unset(
					int pipe_before, t_cmd *cmd, t_data_env *data_env);
int				ft_exec_export(
					int pipe_before, t_cmd *cmd, t_data_env *data_env);
int				ft_exec_exit(int pipe_before, t_cmd *cmd);

// ft_execute.c
void			ft_execute(t_token *tklist_head, t_data_env *data_env);
void			ft_waitpid(t_cmd *cmd);
int				ft_exec_cmd(t_cmd *cmd, t_data_env *data_env);
int				ft_exe_builtin1(
					t_cmd *cmd, t_data_env *data_env, int pipe_before);

// ft_fill_cmd_type_r.c
void			ft_fill_cmd_for_type_r(t_cmd *cmd, t_token *lst);
void			ft_fill_cmd_for_type_r2(t_cmd *cmd, t_token *lst);

// ft_fill_cmd.c
void			ft_fill_cmd(t_cmd *cmd, t_token *lst);
void			ft_fill_argc_argv(t_cmd *cmd, t_token *lst);
void			ft_split_cmd_option(t_cmd *cmd, t_token *lst);
void			ft_malloc_argv(t_cmd *cmd, t_token *lst);

// ft_fork.c
void			ft_fork(t_cmd *cmd, t_data_env *data_env);
void			ft_redirections(t_cmd *cmd);
void			ft_exe_builtin2(t_cmd *cmd, t_data_env *data_env);
void			ft_exec_not_builtin(t_cmd *cmd, t_data_env *data_env);
void			ft_after_fork_parent(t_cmd *cmd);

// ft_free_cmd.c
void			ft_free_cmd(t_cmd *cmd);

// ft_get_cmd.c
t_token			*ft_get_cmd(t_token *tklist_head, t_cmd *cmd);

// ft_init_cmd.c
void			ft_init_cmd(t_cmd *cmd);

//ft_heredoc.c
void			fetch_heredoc(t_cmd *cmd, t_token *tklist_head);

/////////////////////////////// BUILTINS /////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ft_builtins_utils.c 
void			ft_error_identifier(char *builtin, char *identifier);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);

// ft_builtins_utils_2.c
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_srch(char const c, char const *str);
char			*ft_strjoin(char const *s1, char const *s2);

// ft_cd.c
void			ft_error_file(char *builtin, char *file);
int				ft_cd_without_arg(t_data_env *s_data_env);
void			ft_cd_too_many_args(void);
void			ft_cd(int argc, char **argv, t_data_env *s_data_env);

// ft_cd_utils.c
int				ft_update_oldpwd_utils(t_data_env *s_data_env, char *oldpwd);
int				ft_update_oldpwd(t_data_env *s_data_env);
void			ft_update_pwd(char *pwd, t_data_env *s_data_env);
char			*ft_get_pwd(void);

// ft_echo.c
int				ft_check_option(char *str);
void			ft_echo(int argc, char **argv);

// ft_env.c
void			ft_env(char **envp);

// ft_environment_utils_2.c 
int				ft_strcmp_env(const char *s1, const char *s2);
int				ft_compute_env_len(char **envp);
char			**ft_strdup_env(char **envp);

// ft_environment_utils.c
int				ft_remove_var_in_env(int i, t_data_env *s_data_env);
char			**ft_add_var_env(t_data_env *s_data_env, char *new_var);
void			ft_free_env(char **env, int size);

// ft_export_utils.c
int				ft_check_identifier(char **argv, int *j, int i);
void			ft_print_export(char *str);
void			ft_get_env_min(char **min, int *pos_min, int size, char **env);
int				ft_print_env_min(char **env, int size);
int				ft_check_is_first_digit(char **argv, int *j, char *cmd);

// ft_export.c
int				ft_check_var_format_export(char **argv, int *j);
int				ft_last_check_format_export(char **argv, int *j);
void			ft_export_without_arg(t_data_env *s_data_env);
void			ft_export_with_arguments(
					char **argv, t_data_env *s_data_env, int j);
void			ft_export(int argc, char **argv, t_data_env *s_data_env);

// ft_pwd.c
void			ft_pwd(void);

// ft_unset.c
int				ft_check_var_format_unset(char **argv, int *j);
int				ft_unset_with_arg(char **argv, t_data_env *s_data_env, int j);
void			ft_unset(int argc, char **argv, t_data_env *s_data_env);

// ft_exit_utils.c
int				ft_check_all_digits(char *str);
void			ft_error_numeric(char *builtin, char *identifier);
int				ft_check_numeric_arg(char **argv, int inside_pipe);

// ft_exit.c
unsigned char	ft_atoi_exit(char *str);
void			ft_exit_utils(int status, int no_exit_written);
void			ft_exit(int argc, char **argv);

/////////////////////////////// SIGNALS //////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ft_signals.c
void			handler_function(int signum, siginfo_t *siginfo, void *ptr);
void			ft_sigquit(int signum, siginfo_t *siginfo);
void			ft_init_signals(void);

/////////////////////////// GLOBAL VARIABLE //////////////////////////////
typedef struct s_minishell
{
	t_data_env	data_env;
	t_cmd		cmd;
	t_lexing	ltable;
	int			exit_status;
	int			monitor;
	int			status_done;
}				t_minishell;

extern t_minishell	g_minishell;

/////////////////////////////// MAIN / INIT //////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ft_init.c
void			init_table(t_lexing *ltable);
void			ft_init_data_env(t_data_env *s_data_env, char **envp);
void			ft_init_g_minishell(t_minishell *g_minishell, char **envp);

// minishell.c
int				define_token_types(t_lexing *ltable, t_data_env *data_env);
int				minishell(t_lexing *ltable, t_data_env *data_env);

#endif