/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:13:48 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/11 18:02:42 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	define_args(t_lexing *ltable)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (!browse->type)
			browse->type = 'A';
		browse = browse->next;
	}
}

char	*find_cmd_path(char	*cmd_name, char **envp)
{
	int		i;
	char	*cmd;
	char	*cmd_path;
	char	**possible_paths;

	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	possible_paths = ft_split(*envp + 5, ':');
	i = -1;
	while (possible_paths[++i])
	{
		cmd = ft_strjoin("/", cmd_name);
		cmd_path = ft_strjoin(possible_paths[i], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free_array(possible_paths);
			free (cmd);
			return (cmd_path);
		}
		free (cmd);
		free (cmd_path);
	}
	free_array(possible_paths);
	return (0);
}

int	merge_flags(t_lexing *ltable)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse->next)
	{
		if (browse->type == 'C' && browse->next->content[0] == '-')
		{
			browse = tk_merge(&ltable->tklist_head, browse, browse->next);
			if (!browse)
				return (0);
			browse->type = 'C';
		}
		if (browse->next)
			browse = browse->next;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_access(t_token *token, t_data_env *data_env)
{
	char	*cmd_path;

	if (!access(token->content, X_OK))
		token->type = 'C';
	else
	{
		cmd_path = find_cmd_path(token->content, data_env->envp);
		if (cmd_path)
		{
			token->type = 'C';
			free(cmd_path);
		}
	}
	if (ft_strcmp("cd", token->content) == 0)
		token->type = 'C';
	else if (ft_strcmp("pwd", token->content) == 0)
		token->type = 'C';
	else if (ft_strcmp("unset", token->content) == 0)
		token->type = 'C';
	else if (ft_strcmp("env", token->content) == 0)
		token->type = 'C';
	else if (ft_strcmp("export", token->content) == 0)
		token->type = 'C';
	else if (ft_strcmp("echo", token->content) == 0)
		token->type = 'C';
	else if (ft_strcmp("exit", token->content) == 0)
		token->type = 'C';
	return (1);
}

int	define_cmds(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (!browse->type)
			check_access(browse, data_env);
		while (browse && browse->type != 'R' && browse->type != 'D')
			browse = browse->next;
		if (browse && browse->content[0] == '<')
		{
			if (browse->next)
			{
				if (browse->next->next && !browse->next->next->type)
					check_access(browse->next->next, data_env);
			}
		}
		if (browse)
			browse = browse->next;
	}
	if (!merge_flags(ltable))
		return (free_structs(ltable, data_env,
				"Token merge failure\n", 1));
	return (1);
}
