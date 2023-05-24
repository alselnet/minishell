/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:06:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/24 17:16:19 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	define_redirs(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (ft_isinbase(browse->content[0], "<|>"))
			browse->type = 'R';
		browse = browse->next;
	}
	browse = ltable->tklist_head;
	while (browse->next)
	{
		if (browse->type && browse->type == browse->next->type)
			return (free_structs(ltable, data_env,
					"Consecutive redirections\n", 1));
		browse = browse->next;
	}
	return (1);
}

void	define_delims(t_lexing *ltable)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse->next)
	{
		if (!ft_strncmp(browse->content, "<<", 2))
			browse->next->type = 'D';
		browse = browse->next;
	}
}

void	type_file(t_token *token)
{
	int	fd;

	fd = 0;
	fd = open(token->content, O_RDONLY, 0777);
	if (fd > -1)
	{
		token->type = 'F';
		close (fd);
	}
	else if (token->prev)
	{
		if ((token->prev->content[0] == '>' && !token->prev->content[1])
			|| (!ft_strncmp(token->prev->content, ">>", 2)))
			token->type = 'F';
	}
}

void	define_files(t_lexing *ltable)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (!browse->type)
			type_file(browse);
		browse = browse->next;
	}
}

int	define_token_types(t_lexing *ltable, t_data_env *data_env)
{
	int	monitor;

	monitor = define_redirs(ltable, data_env);
	if (monitor)
		define_delims(ltable);
	if (monitor)
		define_cmds(ltable, data_env);
	if (monitor)
		define_files(ltable);
	if (monitor)
		define_args(ltable);
	if (!monitor)
		return (0);
	return (1);
}
