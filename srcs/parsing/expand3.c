/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:05 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/04 19:59:02 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		to_expand(t_token *browse)
{
	int	i;

	i = -1;
	while(browse->content[++i])
	{
		while(browse->content[i] && browse->content[i] != '$')
		{
			if (ft_isalnum(browse->content[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

t_token	*expand_process(t_lexing *ltable, t_data_env *data_env, t_token *browse)
{
	if (ft_isinbase('$', browse->content)
		&& !ft_isinbase(browse->content[0], "\'"))
	{
		if (!ft_strncmp(browse->content, "$?", 2)
			&& ft_strlen(browse->content) == 2)
		{
			free(browse->content);
			browse->content = ft_itoa(g_minishell.exit_status);
		}
		else if(!to_expand(browse))
			return (browse);
		browse = expand_token(browse,ltable, data_env);
		if (!browse || !ltable->tklist_head)
			return (0);
	}
	return (browse);
}
