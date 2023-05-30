/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:13:57 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/30 16:27:20 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token **head)
{
	t_token	*browse;
	int		i;

	i = 0;
	if (!head || !*head)
		return ;
	browse = *head;
	while (browse)
	{
		printf("token %d contains %s\n", i, browse->content);
		printf("\ttoken type is %c\n\n", browse->type);
		browse = browse->next;
		i++;
	}
}

void	rev_print_token_list(t_token **last, t_token **head)
{
	t_token	*browse;
	int		i;

	i = 0;
	if (!head || !*head || !last || !*last)
		return ;
	browse = *last;
	while (browse)
	{
		printf("token %d contains %s\n",
			tk_size(*head) - i - 1, browse->content);
		browse = browse->prev;
		i++;
	}
}
