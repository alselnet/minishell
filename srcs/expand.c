/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:30:57 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/25 18:38:07 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	g_monitor;

void	update_token_content(t_token *token, char *variable)
{
	int		i;
	char	*newcontent;

	i = 0;
	while (token->content[i])
		i++;
	while (token->content[--i] != '$')
		token->content[i] = 0;
	token->content[i] = 0;
	newcontent = ft_strjoin(token->content, variable);
	free(token->content);
	token->content = newcontent;
}

int	expand_token(t_token *token, t_lexing *ltable, t_data_env *data_env)
{
	char	*cursor;
	char	**env;
	char	*variable;
	int		i;

	i = 0;
	cursor = token->content;
	env = data_env->envp;
	while (cursor && *cursor != '$')
		cursor++;
	cursor++;
	while (*(cursor + i))
		i++;
	while (env && *env && ft_strncmp(cursor, *env, i - 1) != 0)
		env++;
	if (!*env || !**env)
		return (free_structs(ltable, data_env, "Variable not found\n", 1));
	variable = extract_variable_value(env);
	if (!variable)
		return (free_structs(ltable, data_env, "Variable expand failed\n", 1));
	update_token_content(token, variable);
	free(variable);
	return (1);
}

char	*clean_up_quotes(char *oldcontent,
			t_lexing *ltable, t_data_env *data_env)
{
	char	*newcontent;

	newcontent = ft_strtrim(oldcontent, "\'\"");
	if (!newcontent)
	{
		free_structs(ltable, data_env, "Variable expand failed\n", 1);
		return (0);
	}
	return (newcontent);
}

int	format_tokens(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;
	char	*no_quote_content;

	browse = ltable->tklist_head;
	no_quote_content = 0;
	while (browse)
	{
		if (ft_isinbase('\'', browse->content)
			|| ft_isinbase('\"', browse->content))
		{
			no_quote_content
				= clean_up_quotes(browse->content, ltable, data_env);
			if (!no_quote_content)
				return (0);
			free(browse->content);
			browse->content = no_quote_content;
		}
		browse = browse->next;
	}
	return (1);
}

int	expand_token_list(t_lexing *ltable, t_data_env *data_env)
{
	t_token	*browse;

	browse = ltable->tklist_head;
	while (browse)
	{
		if (ft_isinbase('$', browse->content)
			&& !ft_isinbase(browse->content[0], "\'"))
		{
			if (!ft_strncmp(browse->content, "$?", 2)
				&& ft_strlen(browse->content) == 2)
			{
				free(browse->content);
				browse->content = ft_itoa(g_monitor);
			}
			else
			{
				if (!expand_token(browse, ltable, data_env))
					return (0);
			}
		}
		browse = browse->next;
	}
	if (!format_tokens(ltable, data_env))
		return (0);
	return (1);
}
