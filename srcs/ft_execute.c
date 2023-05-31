/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:20 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/31 19:07:18 by orazafy          ###   ########.fr       */
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
	//error to handle
	if (lst->next == NULL)
		return (result);
	if (lst->next->type != 'A')
			return (result);
	while (lst->next->type == 'A')
	{
		result = ft_strjoin_free(result, " ");
		// error to handle
		result = ft_strjoin_free(result, lst->next->content);
		//error to handle
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

int	ft_fill_cmd(t_cmd *cmd, t_token *lst)
{
	if (lst->type == 'R')
	{
		if (lst->content[0] == '<')
		{
			// We will have to make sure that after "<" we have a file
			if (cmd->fd_in == -1)
				return (0);
			cmd->fd_in = open(lst->next->content, O_RDONLY, 0500);
			if (cmd->fd_in == -1)
				ft_error_no_such_file(lst->next->content);
		}
		if (lst->content[0] == '>')
		{
			// We will have to make sure that after ">" we have a file
			if (lst->content[1] == '>')
				// protect open !
				cmd->fd_out = open(lst->next->content, O_CREAT | O_WRONLY | O_APPEND, 0664);
			else
				cmd->fd_out = open(lst->next->content, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		}
	}
	if (lst->type == 'C')
	{
		cmd->cmd_value = ft_merge_cmd(lst);
		if (cmd->cmd_value == NULL)
			return (-1);
		cmd->has_cmd = 1;
	}
	if (lst->type == 'A')
	{
		if (cmd->first_arg_done != 1)
			cmd->first_arg = ft_strdup(lst->content);
		if (cmd->first_arg == NULL)
			return (-1);
		cmd->first_arg_done = 1;
	}
	return (0);
}

t_token	*ft_get_cmd(t_token *tklist_head, t_cmd *cmd)
{
	t_token	*lst;

	lst = tklist_head;
	while (lst != NULL)
	{
		if (lst->content[0] == '|')
			break ;
		if (ft_fill_cmd(cmd, lst) == -1)
		{
			// here error to handle later
			return (NULL);
		}
		lst = lst->next;
	}
	if (cmd->has_cmd == 1)
	{
		ft_fill_argc(cmd);
		cmd->argv = ft_split(cmd->cmd_value, ' ');
	}	
	// error to handle
	if (lst == NULL)
	{
		cmd->final_cmd = 1;
		return (lst);
	}
	if (lst->content[0] == '|')
	{
		cmd->pipe = 1;
		lst = lst->next;// The 'next' for the main loop 'while (cmd.final_cmd != 1)
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

	if (cmd->pipe == 1)
	{
		if (pipe(pipefd) < 0)
		// handle error
			perror("");
	}
	cmd->pid = fork();
	if (cmd->final_cmd)
		cmd->final_pid = cmd->pid;
	if (cmd->pid < 0)
	{
		// handle error
		perror("");
	}
	else if (cmd->pid == 0)
	{
		if (cmd->fd_in != -2 && cmd->fd_in != -1)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out != -2)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		if (cmd->pipe == 1)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		if (cmd->fd_in == -1)
		{
			exit(1);
		}
			
		if (cmd->has_cmd == 0)
			ft_error_cmd_not_found(cmd->first_arg);
		cmd->cmd_path = find_cmd_path(cmd->argv[0], data_env->envp);
		// protection here ?
		execve(cmd->cmd_path, cmd->argv, data_env->envp);
		// // error to handle 
		perror("");
		exit(1);
	}
	else
	{
		if (cmd->pipe == 1)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		if (cmd->final_cmd == 1)
		{
			dup2(data_env->stdin, STDIN_FILENO);
			close(data_env->stdin);
			data_env->stdin_closed = 1;
			dup2(data_env->stdout, STDOUT_FILENO);
			close(data_env->stdout);
			data_env->stdout_closed = 1;
		}	
	}
}

void	ft_execute(t_token *tklist_head, t_data_env *data_env)
{
	t_cmd	cmd;
	int		status;
	int		current_pid;
	// int		final_status;
	
	status = 0;
	current_pid = 0;
	// final_status = 0;
	cmd.final_cmd = 0;
	// IL FAUDRA FERMER CES DESCRIPTEURS DE FICHIER SI ON EXIT
	data_env->stdin_closed = 0;
	data_env->stdout_closed = 0;
	data_env->stdin = dup(STDIN_FILENO);
	data_env->stdout = dup(STDOUT_FILENO);
	while (1)
	{
		ft_init_cmd(&cmd);
		tklist_head = ft_get_cmd(tklist_head, &cmd);
		// error to handle, for the return of ft_get_cmd;
		ft_fork(&cmd, data_env);
		if (cmd.final_cmd == 1)
			break ;
		ft_free_cmd(&cmd);
	}
	ft_free_cmd(&cmd);
	
	while (current_pid != -1)
	{
		current_pid = waitpid(cmd.pid, &status, 0);
		// if (cmd.final_pid == current_pid)
		// 	// final_status = status;
		// {
		// 	if (WIFEXITED(status))
		// 		final_status = WEXITSTATUS(status);
		// }
	}
}