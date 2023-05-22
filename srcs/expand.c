/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:30:57 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/22 20:23:00 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_value(char **env)
{
	char	*full_var;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full_var = *env;
	while(full_var[i] && full_var[i] != '=')
		i++;
	if (!full_var[i])
		return (0);
	j += i + 1;
	while(full_var[j] && full_var[j] != '\n')
		j++;
	if (j < 1)
		return (0);
	value = ft_substr(*env + i + 1, 0, j);
	if (!value)
		return (0);
	return (value);
}

void	update_token_content(t_token *token, char *variable)
{
	int		i;
	char *newcontent;

	i = -1;
	while(token->content[++i]);
	while(token->content[--i] != '$')
		token->content[i] = 0;
	token->content[i] = 0;
	newcontent = ft_strjoin(token->content, variable);
	free(token->content);
	token->content = newcontent;
}

void	expand_token(t_token *token, t_lexing *ltable, t_data_env *data_env)
{
	char	*cursor;
	char	**env;
	char	*variable;
	int		i;

	i = -1;
	cursor = token->content;
	env = data_env->envp;
	printf("ok\n");
	while(cursor && *cursor != '$')
		cursor++;
	if (*(cursor + 1) == '?')
		printf("$? special case\n");
	cursor++;
	while(*(cursor + ++i));
	while (env && *env && ft_strncmp(cursor, *env, i) != 0)
		env++;
	if (!*env || !**env)
		quit(ltable, "Variable not found",1);
	variable = extract_value(env);
	if (!variable)
		quit(ltable, "Variable expand failed",1);
	update_token_content(token, variable);
	free(variable);
}

void	expand_token_list(t_lexing *ltable, t_data_env *data_env)
{
	t_token *browse;

	browse = ltable->tklist_head;
	while(browse)
	{
		if(ft_isinbase('$', browse->content)
			&& !ft_isinbase(browse->content[0], "\'"))
			expand_token(browse, ltable, data_env);
		browse = browse->next;
	}
}