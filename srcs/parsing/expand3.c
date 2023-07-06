/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:05 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 03:10:01 by aselnet          ###   ########.fr       */
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

int	to_expand(char *content)
{
	int	i;

	i = -1;
	while(content[++i])
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

int		fetch_value_len(char **env)
{
	int	len;

	len = 0;
	while(**(env + len) && **(env + len) != '\n')
		len++;
	return (len);
}

void	replace_with_value (char *content, char **cursor, int name_len, char **env)
{
	char	*variable;
	char	*new_content;
	int		value_len;

	variable = extract_variable_value(env);
	value_len = fetch_value_len(env);
	new_con

}

char	*expand_variable(char *content, t_data_env *data_env)
{
	char	*cursor;
	char	**env;
	int		name_len;

	cursor = content;
	while (cursor)
	{
		name_len = 0;
		env = data_env->envp;
		while (cursor && *cursor != '$')
			cursor++;
		while (*(cursor + name_len + 1) && (ft_isalnum(*(cursor + name_len + 1))))
			name_len++;
		while (name_len && env && *env && ft_strenvcmp(cursor + 1, *env, name_len) != 0)
			env++;
		if (name_len && *env && **env)
			replace_with_value(content, &cursor, name_len, env);
		else if (*(cursor + 1) == '?')
			fetch_error_code(content, &cursor);
		else
			cursor++;
	}
	return (content);
}

char	*expand_process(t_lexing *ltable, t_data_env *data_env, char *content)
{
	if (ft_isinbase('$', content) && content[0] != '\'')
	{
		content = expand_variable(content, data_env);
		if (!content)
			return (0);
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