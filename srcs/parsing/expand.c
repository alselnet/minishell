/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:30:57 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/03 15:24:49 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_token_content(t_token *token, char *variable)
{
	if (!check_token_end(token))
	{
		if (!update_content_full(token, variable))
			return (0);
	}
	else if (check_token_end(token))
	{
		if (!update_content_partial(token, variable))
			return (0);
	}
	return (1);
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
	while (*(cursor + i) && (ft_isalnum(*(cursor + i))))
		i++;
	while (env && *env && ft_strenvcmp(cursor, *env, i) != 0)
		env++;
	if (!*env || !**env)
		token = tk_delone_and_link(&ltable->tklist_head, token);
	if (!*env || !**env)
		return (1);
	variable = extract_variable_value(env);
	if (!variable)
		return (free_structs(ltable, data_env, "cannot allocate memory\n", 3));
	if (!update_token_content(token, variable))
		return (free_structs(ltable, data_env, "cannot allocate memory\n", 3));
	return (1);
}

char	*clean_up_quotes(char *oldcontent,
			t_lexing *ltable, t_data_env *data_env)
{
	char	*newcontent;

	if (ft_strlen(oldcontent) < 2)
		return (0);
	newcontent = ft_calloc(sizeof(char), ft_strlen(oldcontent) - 1);
	if (!newcontent)
	{
		free_structs(ltable, data_env, "cannot allocate memory", 3);
		return (0);
	}
	ft_strlcpy(newcontent, oldcontent + 1, ft_strlen(oldcontent) - 1);
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
		if (browse->content && (ft_isinbase('\'', browse->content)
				|| ft_isinbase('\"', browse->content)))
		{
			no_quote_content
				= clean_up_quotes(browse->content, ltable, data_env);
			if (!no_quote_content)
				return (1);
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
				browse->content = ft_itoa(g_minishell.exit_status);
			}
			else if (!expand_token(browse, ltable, data_env)
				|| !ltable->tklist_head)
				return (0);
		}
		browse = browse->next;
	}
	if (!format_tokens(ltable, data_env))
		return (0);
	return (1);
}
