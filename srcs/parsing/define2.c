/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:13:48 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/26 03:05:19 by aselnet          ###   ########.fr       */
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

void	check_access(t_token *token, t_data_env *data_env)
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
}

void	access_cmds(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	if (check_path(data_env->envp))
		return ;
	while (browse)
	{
		if (!browse->type)
			check_access(browse, data_env);
		while (browse && browse->type != 'R' && browse->type != 'D')
			browse = browse->next;
		if (browse && browse->content[0] == '<') // a regarder
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
	return ;
}

int	define_cmds(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	access_cmds(ltable, data_env);
	while (browse)
	{
		if (!browse->type)
		{
			if (!check_builtins(browse))
				browse->type = 'C';
		}
		browse = browse->next;
	}
	if (!merge_flags(ltable))
		return (free_structs(ltable, data_env,
				"Token merge failure\n", 1));
	return (1);
}
