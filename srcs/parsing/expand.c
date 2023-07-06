/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:30:57 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 01:54:34 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_token_content(t_token *token, char *variable)
{
	if (!check_token_end(token->content))
	{
		token->content = update_content_full(token->content, variable);
		if (!token->content)
			return (0);
	}
	else
	{
		token->content = update_content_partial(token->content, variable);
		if (!token->content)
			return (0);
	}
	return (1);
}

char	*expand_token(char *content, t_lexing *ltable, t_data_env *data_env)
{
	char	*cursor;
	char	**env;
	char	*variable;
	int		i;

	i = 0;
	cursor = content;
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
		return (content);
	variable = extract_variable_value(env);
	if (!variable)
		return (0);
	if (!update_token_content(token, variable))
		return (0);
	return (token);
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
		if (browse->content && (browse->content[0] == '\''
				|| browse->content[0] == '\"'))
		{
			if (browse->prev && !ft_strncmp(browse->prev->content, "<<", 2))
				browse->delim_quote = 1;
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
		if (!browse->prev || (browse->prev && ft_strncmp(browse->prev->content, "<<", 2)))
			browse->content = expand_process(ltable, data_env, browse->content);
		if (!browse->content)
			return (free_structs(ltable, data_env, "cannot allocate memory\n", 3));
		else if(browse->content[0] = ' ')
			browse = tk_delone_and_link(&ltable->tklist_head, browse);
		browse = browse->next;
	}
	if (!format_tokens(ltable, data_env))
		return (0);
	return (1);
}
