/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:06:17 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/23 17:59:12 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	i--;
	return (str[i]);
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
			return (free_structs(ltable, data_env, "error : single \'", 1));
		else if (browse->content[0] == '\"'
			&& (ft_strlen(browse->content) == 1
				|| last_char(browse->content) != '\"'))
			return (free_structs(ltable, data_env, "error : single \"", 1));
		else if (ft_strmatch(browse->content, "<|>"))
		{
			if (!browse->next || (ft_strlen(browse->content) > 1
					&& browse->content[0] != browse->content[1]))
				return (free_structs(ltable, data_env,
						"wrong redirection", 1));
			else if (browse->content[0] == '|' && browse->content[1] == '|')
				return (free_structs(ltable, data_env, "|| not supported", 1));
		}
		browse = browse->next;
	}
	return (1);
}
