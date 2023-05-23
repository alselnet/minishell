/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:30:57 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/23 18:55:02 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (*(cursor + 1) == '?')
		printf("$? special case\n");
	cursor++;
	while (*(cursor + i))
		i++;
	while (env && *env && ft_strncmp(cursor, *env, i - 1) != 0)
		env++;
	if (!*env || !**env)
		return (free_structs(ltable, data_env, "Variable not found", 1));
	variable = extract_variable_value(env);
	if (!variable)
		return (free_structs(ltable, data_env, "Variable expand failed", 1));
	update_token_content(token, variable);
	free(variable);
	return (1);
}

char	*clean_up_quotes(char *oldcontent,
			t_lexing *ltable, t_data_env *data_env)
{
	char	*newcontent;
	int		i;
	int		j;

	i = -1;
	j = -1;
	newcontent = ft_strtrim(oldcontent, "\'\"");
	if (!newcontent)
	{
		free_structs(ltable, data_env, "Variable expand failed", 1);
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
			if (!expand_token(browse, ltable, data_env))
				return (0);
		browse = browse->next;
	}
	if (!format_tokens(ltable, data_env))
		return (0);
	return (1);
}
