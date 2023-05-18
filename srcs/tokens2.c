/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:52:25 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 18:12:02 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tk_add_back(t_token **head, t_token *new)
{
	t_token	*browse;

	if (!head || !new)
		return ;
	browse = *head;
	if (*head)
	{
		browse = tk_last(*head);
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

	if (!head || !*head || !new || pos <= 0 || pos > tk_size(*head))
		return ;
	count = 0;
	browse = *head;
	while (++count < pos && browse)
		browse = browse->next;
	new->next = browse->next;
	browse->next = new;
	new->prev = browse;
	if (new->next)
		new->next->prev = new;
}

void	tk_moveto(t_token	**head, t_token *token, int pos)
{
	if (!head || pos < 0 || pos > tk_size(*head) || (!*head && pos))
		return ;
	if (token->next)
		token->next->prev = token->prev;
	if (token->prev)
		token->prev->next = token->next;
	token->prev = 0;
	token->next = 0;
	tk_addto(head, token, pos);
}

/*void	tk_deftype(t_token *token, char *type)
{
//waiting for complete parser
}*/