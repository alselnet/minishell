/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:22:11 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/19 18:11:22 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// NOTE POUR PLUS TARD :
// CE FICHIER PART DU PRINCIPE QUE LA STR RENVOYEE PAR READLINE
// EST TOUJOURS NULL-TERMINATED

void	create_redir_token(t_lexing *ltable, int *reader)
{
	t_token	*new;
	char	redir;

	new = 0;
	redir = ltable->input[*reader];
	if (ltable->input[*reader + 1] == redir)
	{
		new = tk_new(ft_substr(ltable->input, *reader, 2));
		*reader = *reader + 1;
	}
	else
		new = tk_new(ft_substr(ltable->input, *reader, 1));
	if (!new->content)
		quit(ltable, "Unable to allocate token content", 1);
	tk_add_back(&ltable->tklist_head, new);
	*reader = *reader + 1;
}

int	find_quote_len(t_lexing *ltable, int reader, char quote_char)
{
	int	count;

	count = 2;
	while (ltable->input[++reader] && ltable->input[reader] != quote_char)
		count++ ;
	if (ltable->input[reader] == 0)
		return (0);
	return (count);
}

void	create_quoted_token(t_lexing *ltable, int *reader)
{
	t_token	*new;
	char	quote_char;
	int		quote_len;

	new = 0;
	quote_char = ltable->input[*reader];
	quote_len = find_quote_len(ltable, *reader, quote_char);
	if (!quote_len)
		quit(ltable, "Syntax error", 1);
	new = tk_new(ft_substr(ltable->input, *reader, quote_len));
	if (!new->content)
		quit(ltable, "Unable to allocate token content", 1);
	tk_add_back(&ltable->tklist_head, new);
	*reader += quote_len;
}

void	create_regular_token(t_lexing *ltable, int *reader)
{
	t_token	*new;
	int		count;

	new = 0;
	count = 0;
	while (ltable->input[*reader + count]
		&& !ft_isinbase(ltable->input[*reader + count], "<|>\'\" \t"))
		count++ ;
	if (!count)
		quit(ltable, "Token length count error", 1);
	new = tk_new(ft_substr(ltable->input, *reader, count));
	if (!new->content)
		quit(ltable, "Unable to allocate token content", 1);
	tk_add_back(&ltable->tklist_head, new);
	*reader += count;
}

void	create_token_list(t_lexing *ltable)
{
	int		reader;

	reader = 0;
	if (!ltable->input)
		quit(ltable, "Unable ton find input", 0);
	while (ltable->input[reader])
	{
		while (ltable->input[reader] == ' ' || ltable->input[reader] == '\t')
			reader++;
		if (ltable->input[reader] && ft_isinbase(ltable->input[reader], "<|>"))
			create_redir_token(ltable, &reader);
		while (ltable->input[reader] && (ltable->input[reader] == ' '
				|| ltable->input[reader] == '\t'))
			reader++;
		if (ltable->input[reader] && ft_isinbase(ltable->input[reader], "\'\""))
			create_quoted_token(ltable, &reader);
		while (ltable->input[reader] && (ltable->input[reader] == ' '
				|| ltable->input[reader] == '\t'))
			reader++;
		if (ltable->input[reader]
			&& !ft_isinbase(ltable->input[reader], "<|>\'\""))
			create_regular_token(ltable, &reader);
	}
}
