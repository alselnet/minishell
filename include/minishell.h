/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:58:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/01 00:58:06 by orazafy          ###   ########.fr       */
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

//ENV
typedef struct s_data_env
{
	int		size;
	char	**envp;
	int		stdin;
	int		stdout;
	int		stdin_closed;
	int		stdout_closed;
}	t_data_env;

char	**ft_strdup_env(char **envp);
void	ft_print_env(t_data_env *s_data_env);
void	ft_remove_var_in_env(int i, t_data_env *s_data_env);
int		ft_compute_env_len(char **envp);
int		ft_strcmp_env(const char *s1, const char *s2);

//PARSING & INDEXING
typedef struct s_token //liste doublement chainée contenant deux variables
{
	char			*content;
	struct s_token	*prev;
	struct s_token	*next;
	char			type;
}	t_token;

typedef struct s_lexing
{
	t_token	*tklist_head;
	char	*input;
	int		tklist_size;
}	t_lexing;

/*adapations de libft_bonus*/
t_token	*tk_new(char	*content);
int		tk_size(t_token *token);
t_token	*tk_last(t_token *token);
void	tk_add_back(t_token **head, t_token *new);
void	tk_delone(t_token *token);
void	tk_clear(t_token **head);

/*nouvelles fonctions*/
void	tk_deftype(t_token *token, char *type);
void	tk_addto(t_token **head, t_token *new, int pos);
void	tk_moveto(t_token	**head, t_token *token, int pos);
t_token	*tk_merge(t_token **head, t_token *token1, t_token *token2);

//fonctions temporaires de test
void	print_token_list(t_token **head);
void	rev_print_token_list(t_token **last, t_token **head);

//UTILS
void	init_table(t_lexing *table);
char	*extract_variable_value(char **env);
int		free_array(char **arr);
int		free_structs(t_lexing *ltable, t_data_env *data_env,
			char *error_msg, char mode);

//PARSING
int		create_token_list(t_lexing *table, t_data_env *data_env);
int		parse_token_list(t_lexing *ltable, t_data_env *data_env);
int		expand_token_list(t_lexing *ltable, t_data_env *data_env);
void	define_args(t_lexing *ltable);
int		define_cmds(t_lexing *ltable, t_data_env *data_env);
int		define_files(t_lexing *ltable, t_data_env *data_env);
int		define_redirs(t_lexing *ltable, t_data_env *data_env);
void	define_delims(t_lexing *ltable);

// EXECUTE
typedef struct	s_cmd
{
	int		argc;
	char	*cmd_value;
	char	**argv;
	int		pipe;
	int		final_cmd;
	int		fd_in;
	int		error_fd_in;
	int		fd_out;
	int		pid;
	char 	*cmd_path;
	int		final_pid;
	int		has_cmd;
	char	*first_arg;
	int		first_arg_done;
}				t_cmd;

// global

typedef struct s_minishell
{
	t_data_env	data_env;
	t_cmd		cmd;
	t_lexing	ltable;
	int	exit_status;
	int monitor;
}				t_minishell;

extern t_minishell	g_minishell;

// ajout sur minishell.c
void	ft_free_env(char **env, int size);
void	ft_error_envp(char *error_msg, t_data_env *s_data_env);
void	ft_init_data_env(t_data_env *s_data_env, char **envp);
void	ft_init_g_minishell(t_minishell *g_minishell, char **envp);
void	handler_function(int signum, siginfo_t *siginfo, void *ptr);
void	ft_init_signals(void);

// ft_execute.c
void	ft_init_cmd(t_cmd *cmd);
void	ft_fill_argc(t_cmd *cmd);
char	*ft_strjoin_free(char *str1, char *str2);
char	*ft_merge_cmd(t_token *lst);
void	ft_error_no_such_file(char *file);
void	ft_fill_cmd(t_cmd *cmd, t_token *lst);
t_token	*ft_get_cmd(t_token *tklist_head, t_cmd *cmd);
void	ft_free_cmd(t_cmd *cmd);
void	ft_error_cmd_not_found(char *cmd);
void	ft_fork(t_cmd *cmd, t_data_env *data_env);
void	ft_error(void);
void	ft_execute(t_token *tklist_head, t_data_env *data_env);

// from define2.c
char	*find_cmd_path(char	*cmd_name, char **envp);

#endif