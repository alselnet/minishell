/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:52:25 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/24 17:33:09 by aselnet          ###   ########.fr       */
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

void	tk_moveto(t_token **head, t_token *token, int pos)
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

int	tk_merge(t_token *token1, t_token *token2)
{
	t_token	*new;
	char	*new_content;
	char	*tmp;

	tmp = ft_strjoin(token1->content, " ");
	if (!tmp)
		return (0);
	new_content = ft_strjoin(tmp, token2->content);
	if (!new_content)
		return (0);
	free (tmp);
	new = tk_new(new_content);
	if (!new)
		return (0);
	new->type = token1->type;
	new->prev = token1->prev;
	new->next = token2->next;
	if (new->prev)
		new->prev->next = new;
	if (new->next)
		new->next->prev = new;
	tk_delone(token1);
	tk_delone(token2);
	return (1);
}
