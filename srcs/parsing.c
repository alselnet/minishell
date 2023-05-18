/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:06:17 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 20:54:41 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_token_list(t_parsing *table)
{
	t_token	*head;
	t_token	*new;
	int		i;

	i = 0;
	table->split_tokens = ft_split(table->input, ' ');
	if (!table->split_tokens)
		quit("Unable to split command\n");
	if (table->split_tokens[i])
	{
		head = tk_new(table->split_tokens[i]);
		table->tklist_head = &head;
	}
	while (table->split_tokens[++i])
	{
		new = tk_new(table->split_tokens[i]);
		tk_add_back(table->tklist_head, new);
	}
	free(table->split_tokens);
}
