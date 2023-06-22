/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:50:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/22 16:27:01 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*extract_variable_value(char **env)
{
	char	*full_var;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full_var = *env;
	while (full_var[i] && full_var[i] != '=')
		i++;
	if (!full_var[i])
		return (0);
	j += i + 1;
	while (full_var[j] && full_var[j] != '\n')
		j++;
	if (j < 1)
		return (0);
	value = ft_substr(*env + i + 1, 0, j);
	if (!value)
		return (0);
	return (value);
}

int	check_token_end(t_token *token)
{
	int	i;

	i = 0;
	while (token->content[i] && token->content[i] != '$')
		i++;
	if (token->content[i])
		i++;
	while (token->content[i] && ft_isalnum(token->content[i]))
		i++;
	if (token->content[i])
		return (1);
	return (0);
}

int	update_content_full(t_token *token, char *variable)
{
	int		i;
	char	*tmp;

	i = 0;
	while (token->content[i] && token->content[i] != '$')
		i++;
	while (token->content [i])
	{
		token->content[i] = 0;
		i++;
	}
	tmp = ft_strjoin(token->content, variable);
	if (!tmp)
		return (0);
	free(token->content);
	free(variable);
	token->content = tmp;
	return (1);
}

int	update_content_partial(t_token *token, char *variable)
{
	char	*end;
	char	*tmp;

	end = fetch_oldcontent_end(token->content);
	if (!update_content_full(token, variable))
		return (0);
	tmp = ft_strjoin(token->content, end);
	if (!tmp)
		return (0);
	free(token->content);
	free(end);
	token->content = tmp;
	return (1);
}
