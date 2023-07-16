/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:37:32 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/16 11:18:51 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl(void)
{
	char	*buffer;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (0);
	read(1, buffer, BUFFER_SIZE);
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
