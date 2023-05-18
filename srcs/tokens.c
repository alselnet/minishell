/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:19:06 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 14:09:30 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_tknew(char *content)
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

int	ft_tksize(t_token *token)
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

t_token	*ft_tklast(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

void	tk_deftype(t_token *token, char *type)
{
//waiting for complete parser
}
