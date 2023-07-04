/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:15:24 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/04 18:38:33 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl(void)
{
	char	*buffer;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (0);
	read(g_minishell.data_env.stdin, buffer, BUFFER_SIZE);
	return (buffer);
}

t_token	*fetch_delim(t_token **cursor)
{
	t_token	*browse;

	browse = *cursor;
	while (browse && browse->content[0] != '|')
	{
		if (browse->content[0] == '<' && browse->content[1] == '<')
		{
			*cursor = browse;
			return (browse->next);
		}
		browse = browse->next;
	}
	*cursor = browse;
	return (0);
}

int	expand_heredoc(char *line, t_data_env *data_env)
{
	char	*cursor;
	char	**env;
	char	*variable;
	int		i;

	i = 0;
	cursor = line;
	env = data_env->envp;
	while (*cursor && *cursor != '$')
		cursor++;
	cursor++;
	while (*(cursor + i) && (ft_isalnum(*(cursor + i))))
		i++;
	while (env && *env && ft_strenvcmp(cursor, *env, i) != 0)
		env++;
	if (!*env || !**env)
		return (1);
	variable = extract_variable_value(env);
	if (!variable)
		return (0); // add free + exit
	if (!update_content_partial(line, variable))
		return (0);
	return (1);
}

int	process_line(char *line, t_token *delim, t_data_env *data_env)
{
	if (delim->delim_quote || !ft_isinbase('$', line)
		|| ft_isinbase(line[0], "\'"))
		return (1);
	if (!expand_heredoc(line, data_env))
		return (0);
	return (1);
}

void	heredoc_process(t_cmd *cmd, t_data_env *data_env, t_token *delim)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = gnl();
		if (!line)
			return ;
		if (*line == 0)
		{
			write(1, "\n", 1);
			free(line);
			return ;
		}
		if (!process_line(line, delim, data_env))
			return ;
		if (ft_strncmp(delim->content,
				line, ft_strlen(delim->content) - 1) == 0)
		{
			free(line);
			return ;
		}
		write(cmd->fd_heredoc, line, BUFFER_SIZE);
		free(line);
	}
}

void	fetch_heredoc(t_cmd *cmd, t_token *tklist_head, t_data_env *data_env)
{
	t_token	*delim;
	t_token	*browse;

	browse = tklist_head;
	if (cmd->fd_heredoc != -2)
	{
		cmd->fd_heredoc = -2;
		unlink(".hdoc.txt");
	}
	delim = fetch_delim(&browse);
	if (!delim)
		return ;
	while (delim)
	{
		cmd->fd_heredoc = open(".hdoc.txt", O_CREAT | O_WRONLY, 0664);
		if (cmd->fd_heredoc < 0)
			ft_error(1);
		heredoc_process(cmd, data_env, delim);
		if (browse && browse->content[0] != '|')
		{
			browse = browse->next;
			delim = fetch_delim(&browse);
		}
		ft_close (&cmd->fd_heredoc);
	}
}
