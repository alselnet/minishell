/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:06:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/02 23:17:55 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	define_files(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	(void)data_env; //en attendant de tester le no invalid file
	browse = ltable->tklist_head;
	while (browse->next)
		browse = browse->next;
	while (browse->prev)
	{
		if (browse->prev->content[0] == '>')
			browse->type = 'F';
		else if (browse->prev->content[0] == '<'
			&& !browse->prev->content[1])
		{
			// if (!access(browse->content, R_OK))
			browse->type = 'F';
			// else
			// 	return (free_structs(ltable, data_env,
			// 			"Invalid infile\n", 1));
		}
		browse = browse->prev;
	}
	return (1);
}