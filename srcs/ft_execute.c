/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:20 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/01 01:33:01 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->argc = 0;
	cmd->cmd_value = NULL;
	cmd->argv = NULL;
	cmd->pipe = 0;
	cmd->final_cmd = 0;
	cmd->fd_in = -2;
	cmd->error_fd_in = 0;
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

// Merge command, options and arguments
char	*ft_merge_cmd(t_token *lst)
{
	char	*result;
	
	result = ft_strdup(lst->content);
	if (result == NULL)
		ft_error();
	if (lst->next == NULL)
		return (result);
	if (lst->next->type != 'A')
			return (result);
	while (lst->next->type == 'A')
	{
		result = ft_strjoin_free(result, " ");
		if (result == NULL)
			ft_error();
		result = ft_strjoin_free(result, lst->next->content);
		if (result == NULL)
			ft_error();
		lst = lst->next;
		if (lst == NULL)
			break ;
		if (lst->next == NULL)
			break ;
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
			cmd->fd_in = open(lst->next->content, O_RDONLY, 0500);
			if (cmd->fd_in == -1)
				ft_error_no_such_file(lst->next->content);
		}
		if (lst->content[0] == '>')
		{
			if (lst->content[1] == '>')
				cmd->fd_out = open(lst->next->content, O_CREAT | O_WRONLY | O_APPEND, 0664);
			else
				cmd->fd_out = open(lst->next->content, O_CREAT | O_WRONLY | O_TRUNC, 0664);
			if (cmd->fd_out == -1)
				ft_error();
		}
	}
	if (lst->type == 'C')
	{
		cmd->cmd_value = ft_merge_cmd(lst);
		if (cmd->cmd_value == NULL)
			ft_error();
		cmd->has_cmd = 1;
	}
	if (lst->type == 'A')
	{
		if (cmd->first_arg_done != 1)
			cmd->first_arg = ft_strdup(lst->content);
		if (cmd->first_arg == NULL)
			ft_error();
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
			ft_error();
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

void	ft_error_cmd_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	ft_fork(t_cmd *cmd, t_data_env *data_env)
{
	int pipefd[2];

	if (cmd->pipe == 1 && cmd->fd_out == -2)
	{
		if (pipe(pipefd) == -1)
			ft_error();	
	}
	cmd->pid = fork();
	if (cmd->final_cmd)
		cmd->final_pid = cmd->pid;
	if (cmd->pid < 0)
		ft_error();
	else if (cmd->pid == 0)
	{
		if (cmd->fd_in != -2 && cmd->fd_in != -1)
		{
			if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
				ft_error();
			close(cmd->fd_in);
		}
		if (cmd->fd_out != -2)
		{
			if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
				ft_error();
			close(cmd->fd_out);
		}
		if (cmd->pipe == 1 && cmd->fd_out == -2)
		{
			close(pipefd[0]);
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				ft_error();
			close(pipefd[1]);
		}
		if (cmd->fd_in == -1)
			exit(1);
		if (cmd->has_cmd == 0)
			ft_error_cmd_not_found(cmd->first_arg);
		cmd->cmd_path = find_cmd_path(cmd->argv[0], data_env->envp);
		if (cmd->cmd_path == NULL)
			ft_error();
		execve(cmd->cmd_path, cmd->argv, data_env->envp);
		perror("");
		exit(1);
	}
	else
	{
		if (cmd->pipe == 1 && cmd->fd_out == -2)
		{
			close(pipefd[1]);
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
				ft_error();
			close(pipefd[0]);
		}
		if (cmd->final_cmd == 1)
		{
			if (dup2(data_env->stdin, STDIN_FILENO) == -1)
				ft_error();
			close(data_env->stdin);
			data_env->stdin_closed = 1;
			if (dup2(data_env->stdout, STDOUT_FILENO) == -1)
				ft_error();
			close(data_env->stdout);
			data_env->stdout_closed = 1;
		}	
	}
}

void	ft_error(void)
{
	perror("");
	if (g_minishell.data_env.stdin_closed == 0)
		close(g_minishell.data_env.stdin);
	if (g_minishell.data_env.stdout_closed == 0)
		close(g_minishell.data_env.stdout);
	ft_free_cmd(&g_minishell.cmd);
	ft_free_env(g_minishell.data_env.envp, g_minishell.data_env.size);
	tk_clear(&g_minishell.ltable.tklist_head);
	free(g_minishell.ltable.input);
	exit(1);
}

void	ft_execute(t_token *tklist_head, t_data_env *data_env)
{
	int		status;
	int		current_pid;
	
	status = 0;
	current_pid = 0;
	g_minishell.cmd.final_cmd = 0;
	ft_init_cmd(&g_minishell.cmd);
	data_env->stdin = dup(STDIN_FILENO);
	if (data_env->stdin == -1)
		ft_error();
	data_env->stdin_closed = 0;
	data_env->stdout = dup(STDOUT_FILENO);
	if (data_env->stdout == -1)
		ft_error();
	data_env->stdout_closed = 0;
	while (1)
	{
		ft_init_cmd(&g_minishell.cmd);
		tklist_head = ft_get_cmd(tklist_head, &g_minishell.cmd);
		ft_fork(&g_minishell.cmd, data_env);
		if (g_minishell.cmd.final_cmd == 1)
			break ;
		ft_free_cmd(&g_minishell.cmd);
	}
	ft_free_cmd(&g_minishell.cmd);
	while (current_pid != -1)
	{
		current_pid = waitpid(g_minishell.cmd.pid, &status, 0);
		if (g_minishell.cmd.final_pid == current_pid)
		{
			if (WIFEXITED(status))
				g_minishell.exit_status = WEXITSTATUS(status);
		}
	}
}


// CTRL + D pour exit pour l'instant. Plus tard, ce sera CTRL + D ou le builtin exit

// Pour Alex:
/*

g_monitor, c'est le contraire le status. C'est 0 si tout va bien, et 1 si ca va mal.
(en code en général, 0 tout va bien, positif ca va mal. Comme dans un main, return 0 si aucun pb)

Lors du changement, au lieu de g_monitor utilise g_minishell.exit_status
J'ai laissé g_monitor pour pas cassé le code, sauf dans $? j'ai déjà remplacé parce que j'avais besoin de checker mes status. 
Par contre dans mon code d'exec, et les signaux et mes builtins, que l'on connectera plus tard, c'est déjà g_minishell.exit_status.

------------------------------------------------------------

Il faut toujours corriger le début du parsing sur certains cas. 

==> Par exemple, ici cat ca devrait etre commande

< test cat | wc -l
token 0 contains <
        token type is R

token 1 contains test
        token type is F

token 2 contains cat
        token type is A

token 3 contains |
        token type is R



==> Par exemple, les BUILTINS, il faut leur donner des types 'C

==> le reste je sais plus..

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

*/
