/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:06:17 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/10 18:41:21 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	return (str[i]);
}

int	no_alnum(char *content)
{	
	int	i;

	i = -1;
	while (content[++i])
	{
		if (ft_isalnum(content[i]))
			return (0);
	}
	return (1);
}

int	parse_token_list(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (browse->content[0] == '\''
			&& (ft_strlen(browse->content) == 1
				|| last_char(browse->content) != '\''))
			return (free_structs(ltable, data_env, "syntax error near '\n", 1));
		else if (browse->content[0] == '\"' && (ft_strlen(browse->content) == 1
				|| last_char(browse->content) != '\"'))
			return (free_structs(ltable, data_env, "syntax error near \"\n", 1));
		else if (ft_strmatch(browse->content, "<|>"))
		{
			if (!browse->next || (ft_strlen(browse->content) > 1
					&& browse->content[0] != browse->content[1]))
				return (free_structs(ltable, data_env,
						"syntax error near redirection\n", 1));
			else if (browse->content[0] == '|' && browse->content[1] == '|')
				return (free_structs(ltable, data_env, "|| not supported\n", 1));
		}
		browse = browse->next;
	}
	return (1);
}

int	join_quotes(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (browse->join_prev)
		{
			browse = tk_merge_quote(&ltable->tklist_head,
					browse->prev, browse);
			if (!browse)
				return (free_structs(ltable, data_env,
						"cannot allocate memory\n", 4));
		}
		if (browse->join_next)
		{
			browse = tk_merge_quote(&ltable->tklist_head,
					browse, browse->next);
			if (!browse)
				return (free_structs(ltable, data_env,
						"cannot allocate memory\n", 4));
		}
		browse = browse ->next;
	}
	return (1);
}

int	parse_redirections(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse->next)
	{
		if (browse->type == 'R' && browse->next->type == 'R')
		{
			if (browse->content[0] != '|' && browse->next->content[0] != '<')
				return (free_structs(ltable, data_env,
						"syntax error: consecutive redirection\n", 1));
		}
		browse = browse->next;
	}
	return (1);
}
