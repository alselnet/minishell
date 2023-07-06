/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:43:05 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 17:10:34 by aselnet          ###   ########.fr       */
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

int		fetch_value_len(char **env)
{
	int		len;
	int		i;
	char	*value;

	len = 0;
	i = 0;
	value = *env;
	while (value[i] && value[i] != '=')
		i++;
	i ++;
	while(value[len + i] && value[len + i] != '\n')
		len++;
	return (len);
}

void	update_content(char *new_content, char *content, char *variable, char **cursor)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = -1;
	while (*(content + i) && content + i != *cursor)
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
	i++;
	while (*(content + i) && ft_isalnum(*(content + i)))
		i++;
	while (variable[++k])
	{
		new_content[j] = variable[k];
		j++;
	}
	*cursor = new_content + j;
	while (*(content + i))
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
}	

void	update_with_error(char *new_content, char *content, char *error_code, char **cursor)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = -1;
	while (*(content + i) && content + i != *cursor)
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
	i += 2;
	while (*(content + i) && ft_isalnum(*(content + i)))
		i++;
	while (error_code[++k])
	{
		new_content[j] = error_code[k];
		j++;
	}
	*cursor = new_content + j;
	while (*(content + i))
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
}	

char	*replace_with_value(char *content, char **cursor, int name_len, char **env)
{
	char	*variable;
	int		content_len;
	char	*new_content;

	variable = extract_variable_value(env);
	if (!variable)
		return (0);
	content_len = ft_strlen(content) - name_len + fetch_value_len(env);
	new_content = ft_calloc(sizeof(char), content_len);
	if (!new_content)
		return (0);
	update_content(new_content, content, variable, cursor);
	free(variable);
	free(content);
	return (new_content);
}

char	*replace_with_error_code(char *content, char **cursor)
{
	char	*error_code;
	int		content_len;
	char	*new_content;

	error_code = ft_itoa(g_minishell.exit_status);
	if (!error_code)
		return (0);
	content_len = ft_strlen(content) + ft_strlen(error_code) - 1;
	new_content = ft_calloc(sizeof(char), content_len);
	if (!new_content)
		return (0);
	update_with_error(new_content, content, error_code, cursor);
	free(error_code);
	free(content);
	return (new_content);
}

char	*delete_name(char *content, char **cursor, int name_len)
{
	char	*new_content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_content = ft_calloc(sizeof(char), ft_strlen(content) - name_len);
	if (!new_content)
		return (0);
	while (*(content + i) && content + i != *cursor)
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
	i++;
	while (*(content + i) && ft_isalnum(*(content + i)))
		i++;
	*cursor = new_content + j;
	while (*(content + i))
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
	free(content);
	return (new_content);
}

char	*expand_variable(char *content, t_data_env *data_env)
{
	char	*cursor;
	char	**env;
	int		name_len;

	cursor = content;
	while (cursor && *cursor)
	{
		name_len = 0;
		env = data_env->envp;
		while (cursor && *cursor && *cursor != '$')
			cursor++;
		while (*(cursor + name_len + 1) && (ft_isalnum(*(cursor + name_len + 1))))
			name_len++;
		while (name_len && env && *env && ft_strenvcmp(cursor + 1, *env, name_len) != 0)
			env++;
		if (*(cursor + 1) == '?')
			content = replace_with_error_code(content, &cursor);
		else if (!*env || !**env)
			content = delete_name(content, &cursor, name_len);
		else if (name_len)
			content = replace_with_value(content, &cursor, name_len, env);
		else
			cursor++;
		if (!content)
			return (0);
	}
	return (content);
}

char	*expand_process(char *content, t_data_env *data_env)
{
	if (ft_isinbase('$', content) && content[0] != '\'')
	{
		content = expand_variable(content, data_env);
		if (!content)
			return (0);
	}
	return(content);
}
