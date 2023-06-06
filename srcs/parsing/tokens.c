/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:19:06 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/30 16:27:24 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tk_new(char *content)
{
	t_token	*new;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->content = content;
	new->type = 0;
	new->prev = 0;
	new->next = 0;
	return (new);
}

int	tk_size(t_token *token)
{
	int		count;

	count = 0;
	while (token)
	{
		token = token->next;
		count++;
	}
	return (count);
}

t_token	*tk_last(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

void	tk_delone(t_token *token)
{
	if (!token)
		return ;
	if (token->content)
		free(token->content);
	free(token);
}

void	tk_clear(t_token **head)
{
	t_token	*browse;

	if (!head)
		return ;
	browse = *head;
	while (*head)
	{
		*head = (*head)->next;
		tk_delone(browse);
		browse = *head;
	}
	*head = 0;
}