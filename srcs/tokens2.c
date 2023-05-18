/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:52:25 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 14:40:30 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_tkdelone(t_token *token)
{
	if (!token)
		return ;
	if (token->content)
		free(token->content);
	if (token->type)
		free(token->type);
	free(token);
}

void	ft_tkclear(t_token **head)
{
	t_token	*browse;

	if (!head)
		return ;
	browse = *head;
	while (*head)
	{
		*head = (*head)->next;
		ft_tkdelone(browse);
		browse = *head;
	}
	*head = 0;
}

void	ft_tkadd_back(t_token **head, t_token *new)
{
	t_token	*browse;

	if (!head || !new)
		return ;
	browse = *head;
	if (*head)
	{
		browse = ft_tklast(*head);
		browse->next = new;
		new->prev = browse;
	}
	else
		*head = new;
}

void	tk_addto(t_token **head, t_token *new, int pos)
{
	t_token	*browse;
	int		count;

	if (!head || new || pos < 0 || pos > ft_tksize(*head) || (!*head && pos != 0))
		return ;
	count = -1;
	browse = *head;
	if (!pos)
	{
		new->prev = browse;
		return;
	}
	while (++count < pos)
		browse = browse->next;
	new->next = browse->next;
	browse->next = new;
	new->prev = browse;
	if (new->next)
		new->next->prev = new;
}

void	tk_moveto(t_token	**head, t_token *token, int pos)
{
	if (!head || pos < 0 || pos > ft_tksize(*head) || (!*head && pos))
		return ;
	token->next->prev = token->prev;
	token->prev->next = token->next;
	token->prev = 0;
	token->next = 0;
	tk_addto(head, token, pos);
}
