/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:20 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/27 00:06:30 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->argc = 0;
	cmd->cmd_value = NULL;
	cmd->argv = NULL;
	cmd->pipe = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->to_append = 0;
	cmd->final_cmd = 0;
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	cmd->pid = 0;
	cmd->cmd_path = NULL;
	cmd->final_pid = 0;
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

int	ft_fill_cmd(t_cmd *cmd, t_token *lst)
{
	if (lst->type == 'R')
	{
		if (lst->content[0] == '<')
		{
			// We will have to make sure that after "<" we have a file
			cmd->infile = ft_strdup(lst->next->content);
			if (cmd->infile == NULL)
				return (-1);
		}
		if (lst->content[0] == '>')
		{
			// We will have to make sure that after ">" we have a file
			cmd->outfile = ft_strdup(lst->next->content);
			if (cmd->outfile == NULL)
				return (-1);
			if (lst->content[1] == '>')
				cmd->to_append = 1;
		}
	}
	if (lst->type == 'C')
	{
		cmd->cmd_value = ft_merge_cmd(lst);
		if (cmd->cmd_value == NULL)
			return (-1);
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
	ft_fill_argc(cmd);
	cmd->argv = ft_split(cmd->cmd_value, ' ');
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
	if (cmd->infile != NULL)
		free(cmd->infile);
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	if (cmd->argv != NULL)
		free_array(cmd->argv);
	if (cmd->cmd_value != NULL)
		free(cmd->cmd_value);
	if (cmd->cmd_path != NULL)
		free(cmd->cmd_path);
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
		if (cmd->infile != NULL)
		{
			cmd->fd_in = open(cmd->infile, O_RDONLY, 0500);
			// protection for open ?
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->outfile != NULL)
		{
			if (cmd->to_append == 0)
				cmd->fd_out = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0664);
				// protection for open ?
			else
				cmd->fd_out = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0664);
				// protection for open ?
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		if (cmd->pipe == 1)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
		}
		cmd->cmd_path = find_cmd_path(cmd->argv[0], data_env->envp);
		// protection here ?
		execve(cmd->cmd_path, cmd->argv, data_env->envp);
		// // error to handle 
		perror("");
	}
	else
	{
		if (cmd->pipe == 1)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
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
		// 	final_status = status;
		// for the global variable exit_status later
	}
}

// PROBLEMS

// 1)

// PROBLEM IN PARSING ---> CAT IS A COMMAND HERE
// PROBLEM
// < test cat | wc -l
// -bash: test: No such file or directory
//        0


// < test cat | wc -l
// token 0 contains <
//         token type is R

// token 1 contains test
//         token type is F

// token 2 contains cat
//         token type is A

// token 3 contains |
//         token type is R


// 2)
// impossible to do valgrind with makefile result

// 3)
/*
Our code:
> cat < ezfk | wc -c
Invalid infile
> 

Bash:
$ cat < zefk | wc -c
bash: zefk: No such file or directory
       0


*/

// 4)
/*
same for 
$jzkfhjzkefh cat | ls -l
redirect error inside the pipe
add a condition if cmd start with argument, execution is "write(2, ......)"
*/

// 5
/*
All errors to handle:
create a global struct with all the data (cmd, data env, ltable etc), to be able to free in case of error
BUT ALSO
when will code exit builtin !! (we will need global variables)
*/

// 6 : update status later (inside the global struct)

// 7: when there is a pipe in readline, the code exit itself instead of showing a new prompt

// 8: connect builtins when everyting is perfect with no builtins

// 9: export, unset etc builtins need to have "C" as type