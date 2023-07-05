/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:50:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 01:37:23 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "../include/minishell.h"

char	*fetch_oldcontent_end(char *oldcontent)
{
	int		i;
	int		j;
	int		k;
	char	*end;

	i = 0;
	j = 0;
	k = -1;
	while (oldcontent[i] && oldcontent[i] != '$')
		i++;
	i++;
	while (oldcontent[i] && ft_isalnum(oldcontent[i]))
		i++;
	while (oldcontent[i + j])
		j++;
	end = ft_calloc(sizeof(char), j + 1);
	if (!end)
		return (0);
	while (oldcontent [i] && ++k < j)
	{
		end[k] = oldcontent[i];
		oldcontent[i] = 0;
		i++;
	}
	return (end);
}



int	check_token_end(char *content)
{
	int	i;

	i = 0;
	while (content[i] && content[i] != '$')
		i++;
	if (content[i])
		i++;
	while (content[i] && ft_isalnum(content[i]))
		i++;
	if (content[i])
		return (1);
	return (0);
}

char	*update_content_full(char *content, char *variable)
{
	int		i;
	char	*tmp;

	i = 0;
	while (content[i] && content[i] != '$')
		i++;
	content[i] = 0;
	tmp = ft_strjoin(content, variable);
	if (!tmp)
		return (0);
	free(content);
	free(variable);
	return (tmp);
}

char	*update_content_partial(char *content, char *variable)
{
	char	*end;
	char	*tmp;

	end = fetch_oldcontent_end(content);
	if (!update_content_full(content, variable))
		return (0);
	tmp = ft_strjoin(content, end);
	if (!tmp)
		return (0);
	free(content);
	free(end);
	return (tmp);
}
