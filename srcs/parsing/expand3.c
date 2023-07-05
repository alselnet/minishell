/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:05 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 01:38:24 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	to_expand(t_token *browse)
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

int	count_variables(char *content)
{
	int	i;
	int	count;

	i = -1;
	count= 0;
	while(content[++i])
	{
		if (content[i] == '$')
			count++;
	}
	return (count);
}

int	fetch_tab_len(char **split_tab)
{
	int	i;

	i = 0;
	while(split_tab[i])
		i++;
	return (i);
}

char	*space_content(char *content)
{
	int		i;
	int		j;
	char	*new_content;

	i = 0;
	j = 0;
	new_content = ft_calloc(sizeof(char), ft_strlen(content) + count_variables(content) + 1);
	if (!new_content)
		return (0);
	while(content[i])
	{
		if (content[i] == '$')
		{
			new_content[j] = ' ';
			new_content[++j] = '$';
		}
		else
			new_content[j] = content[i];
		i++;
		j++;
	}
	free(content);
	return (new_content);
}

void	free_double_arr(char **tab, int split_len)
{
	int	i;
	
	i = -1;
	while(++i < split_len)
		free(tab[i]);
	free(tab);
}

char	*expand_variable(char *content)
{

}

char	*expand_multiple_variables(char *content)
{
	int		i;
	int		split_len;
	char	**split_tab;
	char	*new_content;

	i = -1;
	new_content = space_content(content);
	if (new_content)
		return (0);
	split_tab = ft_split(new_content, ' ');
	if (!split_tab)
		return (0);
	split_len = fetch_tab_len(split_tab);
	while (split_tab[++i])
	{
		split_tab[i] = expand_variable(split_tab[i]);
		if (!split_tab[i])
		{
			split_len = fetch_tab_len(split_tab);
			free_double_arr(split_tab, split_len);
			return (0);
		}
	}
	new_content = join_tab(split_tab, split_len);
	return (new_content);
}

char	*expand_process(t_lexing *ltable, t_data_env *data_env, char *content)
{
	char	*newcontent;

	if (ft_isinbase('$', content) && content[0] != '\'')
	{
		if (count_variables(content) < 2)
			newcontent = expand_variable(content);
		else
			newcontent = expand_multiple_variables(content);
		if (!newcontent)
			return (0);
		return (newcontent);
	}
	return(content);
}

t_token	*old_expand_process(t_lexing *ltable, t_data_env *data_env, t_token *browse)
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