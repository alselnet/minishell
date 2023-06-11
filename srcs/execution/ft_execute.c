/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:20 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/11 20:59:25 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->argc = 0;
	cmd->cmd_value = NULL;
	cmd->argv = NULL;
	cmd->pipe = 0;
	cmd->pipefd[0] = -2;
	cmd->pipefd[1] = -2;
	cmd->final_cmd = 0;
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	cmd->pid = 0;
	cmd->cmd_path = NULL;
	cmd->final_pid = 0;
	cmd->has_cmd = 0;
	cmd->first_arg = NULL;
	cmd->first_arg_done = 0;
}

void	ft_fill_argc(t_cmd *cmd)
{
	char *start;
	char *str;
	
	str = cmd->cmd_value;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		start = str;
		while (*str && *str != ' ')
			str++;
		if (str - start > 0)
			cmd->argc++;
		if (*str != 0)
			str++;
	}
}

char	*ft_strjoin_free(char *str1, char *str2)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	len1;
	ssize_t	len2;
	char	*dest;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	dest = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		dest[i++] = str2[j++];
	}
	dest[i] = 0;
	free(str1);
	return (dest);
}

char	*ft_merge_cmd(t_token *lst)
{
	char	*result;
	
	result = ft_strdup(lst->content);
	if (result == NULL)
		ft_error(1);
	if (lst->next == NULL)
		return (result);
	lst = lst->next;
	while (lst != NULL && lst->content[0] != '|')
	{
		if (lst->type == 'A')
			result = ft_strjoin_free(result, " ");
		if (result == NULL)
			ft_error(1);
		if (lst->type == 'A')
			result = ft_strjoin_free(result, lst->content);
		if (result == NULL)
			ft_error(1);
		lst = lst->next;
	}
	return (result);
}

void	ft_error_no_such_file(char *file)
{
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}

void	ft_fill_cmd(t_cmd *cmd, t_token *lst)
{
	if (lst->type == 'R')
	{
		if (lst->content[0] == '<')
		{
			if (cmd->fd_in == -1)
				return ;
			if (cmd->fd_in != -2)
				close(cmd->fd_in);
			cmd->fd_in = open(lst->next->content, O_RDONLY, 0500);
			if (cmd->fd_in == -1)
				ft_error_no_such_file(lst->next->content);
		}
		if (lst->content[0] == '>')
		{
			if (cmd->fd_out != -2)
				close(cmd->fd_out);
			if (lst->content[1] == '>')
				cmd->fd_out = open(lst->next->content, O_CREAT | O_WRONLY | O_APPEND, 0664);
			else
				cmd->fd_out = open(lst->next->content, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			if (cmd->fd_out == -1)
				ft_error(1);
		}
	}
	if (lst->type == 'C')
	{
		cmd->cmd_value = ft_merge_cmd(lst);
		if (cmd->cmd_value == NULL)
			ft_error(1);
		cmd->has_cmd = 1;
	}
	if (lst->type == 'A')
	{
		if (cmd->first_arg_done != 1)
			cmd->first_arg = ft_strdup(lst->content);
		if (cmd->first_arg == NULL)
			ft_error(1);
		cmd->first_arg_done = 1;
	}
}

t_token	*ft_get_cmd(t_token *tklist_head, t_cmd *cmd)
{
	t_token	*lst;

	lst = tklist_head;
	while (lst != NULL)
	{
		if (lst->content[0] == '|')
			break ;
		ft_fill_cmd(cmd, lst);
		lst = lst->next;
	}
	if (cmd->has_cmd == 1)
	{
		ft_fill_argc(cmd);
		cmd->argv = ft_split(cmd->cmd_value, ' ');
		if (cmd->argv == NULL)
			ft_error(1);
	}
	if (lst == NULL)
	{
		cmd->final_cmd = 1;
		return (lst);
	}
	if (lst->content[0] == '|')
	{
		cmd->pipe = 1;
		lst = lst->next;
	}
	return (lst);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd->argv != NULL)
		free_array(cmd->argv);
	if (cmd->cmd_value != NULL)
		free(cmd->cmd_value);
	if (cmd->cmd_path != NULL)
		free(cmd->cmd_path);
	if (cmd->first_arg != NULL)
		free(cmd->first_arg);
	cmd->argv = NULL;
	cmd->cmd_value = NULL;
	cmd->cmd_path = NULL;
	cmd->first_arg = NULL;
}

void	ft_close(int *fd)
{
	close(*fd);
	*fd = -2;
}

void ft_close_all_fds()
{
	t_cmd cmd;
	t_data_env data_env;

	cmd = g_minishell.cmd;
	data_env = g_minishell.data_env;
	if (data_env.stdin != -2 && data_env.stdin != -1)
		ft_close(&data_env.stdin);
	if (data_env.stdout != -2 && data_env.stdout != -1)
		ft_close(&data_env.stdout);
	if (cmd.fd_in != -2 && cmd.fd_in != -1)
		ft_close(&cmd.fd_in);
	if (cmd.fd_out != -2 && cmd.fd_out != -1)
		ft_close(&cmd.fd_out);
	if (cmd.pipefd[0] != -2 && cmd.pipefd[0] != -1)
		ft_close(&cmd.pipefd[0]);
	if (cmd.pipefd[1] != -2 && cmd.pipefd[1] != -1)
		ft_close(&cmd.pipefd[1]);
}

void	ft_error_cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	ft_close_all_fds();
	exit(127);
}

void	ft_error(int status)
{
	perror("");
	ft_close_all_fds();
	ft_free_cmd(&g_minishell.cmd);
	ft_free_env(g_minishell.data_env.envp, g_minishell.data_env.size);
	tk_clear(&g_minishell.ltable.tklist_head);
	free(g_minishell.ltable.input);
	rl_clear_history();
	exit(status);
}

void	ft_fork(t_cmd *cmd, t_data_env *data_env)
{
	if (cmd->pipe == 1 && cmd->fd_out == -2)
	{
		if (pipe(cmd->pipefd) == -1)
			ft_error(1);	
	}
	cmd->pid = fork();
	if (cmd->final_cmd)
		cmd->final_pid = cmd->pid;
	if (cmd->pid < 0)
		ft_error(1);
	else if (cmd->pid == 0)
	{
		if (cmd->fd_in != -2 && cmd->fd_in != -1)
		{
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
				ft_error(2);
			ft_close(&cmd->fd_in);
		}
		if (cmd->fd_out != -2)
		{
			if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
				ft_error(2);
		}
		if (cmd->pipe == 1 && cmd->fd_out == -2)
		{
			ft_close(&cmd->pipefd[0]);
			if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
				ft_error(2);
			ft_close(&cmd->pipefd[1]);
		}
		if (cmd->fd_out != -2)
			ft_close(&cmd->fd_out);
		if (cmd->fd_in == -1)
		{
			ft_close_all_fds();
			exit(1);
		}
		if (cmd->has_cmd == 0)
			ft_error_cmd_not_found(cmd->first_arg);
		if (ft_strcmp("echo", g_minishell.cmd.argv[0]) == 0)
			ft_echo(g_minishell.cmd.argc, g_minishell.cmd.argv);
		else if (ft_strcmp("env", g_minishell.cmd.argv[0]) == 0)
			ft_env(data_env->envp);
		else if (ft_strcmp("pwd", g_minishell.cmd.argv[0]) == 0)
			ft_pwd();
		else if (ft_strcmp("export", g_minishell.cmd.argv[0]) == 0 && g_minishell.cmd.argc == 1)
			ft_export(g_minishell.cmd.argc, g_minishell.cmd.argv, data_env);
		cmd->cmd_path = find_cmd_path(cmd->argv[0], data_env->envp);
		if (cmd->cmd_path == NULL)
			ft_error(2);
		close(g_minishell.data_env.stdin);
		close(g_minishell.data_env.stdout);
		execve(cmd->cmd_path, cmd->argv, data_env->envp);
		ft_error(2);
	}
	else
	{
		if (cmd->pipe == 1 && cmd->fd_out == -2)
		{
			ft_close(&cmd->pipefd[1]);
			if (dup2(cmd->pipefd[0], STDIN_FILENO) == -1)
				ft_error(1);
			ft_close(&cmd->pipefd[0]);
		}
		if (cmd->fd_in != -2 && cmd->fd_in != -1)
			ft_close(&cmd->fd_in);
		if (cmd->fd_out != -2 && cmd->fd_out != -1)
			ft_close(&cmd->fd_out);
	}
}

void	ft_execute(t_token *tklist_head, t_data_env *data_env)
{
	int		status;
	int		is_builtin_without_stdout;
	int		pipe_before;
	int		null_fd;
	
	status = 0;
	is_builtin_without_stdout = 0;
	pipe_before = 0;
	ft_init_cmd(&g_minishell.cmd);
	data_env->stdin = dup(STDIN_FILENO);
	if (data_env->stdin == -1)
		ft_error(1);
	data_env->stdout = dup(STDOUT_FILENO);
	if (data_env->stdout == -1)
		ft_error(1);
	while (1)
	{
		ft_init_cmd(&g_minishell.cmd);
		tklist_head = ft_get_cmd(tklist_head, &g_minishell.cmd);
		if (g_minishell.cmd.argv != NULL)
		{
			if (ft_strcmp("cd", g_minishell.cmd.argv[0]) == 0)
			{
				if (pipe_before != 1)
					ft_cd(g_minishell.cmd.argc, g_minishell.cmd.argv, data_env);
				if (pipe_before == 1)
					g_minishell.exit_status = 0;
				is_builtin_without_stdout = 1;
			}
			else if (ft_strcmp("unset", g_minishell.cmd.argv[0]) == 0)
			{
				ft_unset(g_minishell.cmd.argc, g_minishell.cmd.argv, data_env);
				is_builtin_without_stdout = 1;
			}	
			else if (ft_strcmp("export", g_minishell.cmd.argv[0]) == 0 && g_minishell.cmd.argc > 1)
			{
				ft_export(g_minishell.cmd.argc, g_minishell.cmd.argv, data_env);
				is_builtin_without_stdout = 1;
			}
			// "Exit" builtin code à peaufiner encore...
			else if (ft_strcmp("exit", g_minishell.cmd.argv[0]) == 0)
			{
				if (pipe_before != 1)
					ft_exit(g_minishell.cmd.argc, g_minishell.cmd.argv);
				if (g_minishell.cmd.argc > 2 && pipe_before == 1)
				{
					write(2, "exit: too many arguments\n", 25);
					g_minishell.exit_status = 1;
				}
				else if (g_minishell.cmd.argc == 2 && pipe_before == 1)
					g_minishell.exit_status = ft_atoi_exit(g_minishell.cmd.argv[1]);
				is_builtin_without_stdout = 1;
			}
			if (is_builtin_without_stdout == 1)
			{
				null_fd = open("/dev/null", O_RDONLY);
				if (dup2(null_fd, STDIN_FILENO) == -1)
				{
					close(null_fd);
					ft_error(1);
				}
				close(null_fd);
			}
		}
		if (is_builtin_without_stdout == 0)
		{
			ft_fork(&g_minishell.cmd, data_env);
			if (waitpid(g_minishell.cmd.pid, &status, 0) == -1)
			{
				if (errno != EINTR)
					ft_error(1);
				break ;
			}
			if (g_minishell.cmd.final_pid != 0)
			{
				if (WIFEXITED(status))
					g_minishell.exit_status = WEXITSTATUS(status);
			}
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) == 2)
					ft_error(1);
			}
		}
		if (g_minishell.cmd.final_cmd == 1)
			break ;
		if (g_minishell.cmd.pipe == 1)
			pipe_before = 1;
		else
			pipe_before = 0;
		ft_free_cmd(&g_minishell.cmd);
		is_builtin_without_stdout = 0;
	}
	if (dup2(data_env->stdin, STDIN_FILENO) == -1)
		ft_error(1);
	ft_close(&data_env->stdin);
	if (dup2(data_env->stdout, STDOUT_FILENO) == -1)
		ft_error(1);
	ft_close(&data_env->stdout);
	ft_close_all_fds();
	ft_free_cmd(&g_minishell.cmd);
}


// Pour Alex:
/*

A VOIR:

g_monitor, c'est le contraire le status. C'est 0 si tout va bien, et 1 si ca va mal.
(en code en général, 0 tout va bien, positif ca va mal. Comme dans un main, return 0 si aucun pb)

Lors du changement, au lieu de g_monitor utilise g_minishell.exit_status
J'ai laissé g_monitor pour pas cassé le code, sauf dans $? j'ai déjà remplacé parce que j'avais besoin de checker mes status. 
Par contre dans mon code d'exec, et les signaux et mes builtins, que l'on connectera plus tard, c'est déjà g_minishell.exit_status.

------------------------------------------------------------

Il faut toujours corriger le début du parsing sur certains cas. 

les histoires de guillemets etc

-------------------------------------------------

Vérifie que t'as bien pris tout en compte les syntaxes error, leurs messages d'erreurs et update g_minishell.exit_status avec le bon status

par exemple : 
$echo > |
-bash: syntax error near unexpected token `|'
$ echo $?
258

--------------------------------------------------

HEREDOC à mettre en place

--------------------------------------------------------

ne pas oublier rl_clear_history si on exit

------

echo $HOME
Variable not found

le vrai bash:
$ echo $VAVA

$

------------

dans tout notre code (parsing, biutlins etc) il faut protéger les recherches d'env. 
parce que si l'user fait "unset" ca enleve toutes les variables d'environnement. Donc ca segfault dans les parties qui cherchent dans env. 

-----

ouvrir/close tous les OUTfiles avant d'entrer dans exec (besoin pour créer le outfile avant meme de commencer l'exec s'il n existe pas)

----

exit builtin à peaufiner encore...

--- 
unset selon les bash, le check_var_format n'est pas nécessaire.

--- 
protection si path n'existe pas ?

--- 
comment simuler l'erreur status 126 ?

----

*/
