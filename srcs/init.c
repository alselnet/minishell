/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:30:15 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 20:47:08 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_table(t_parsing *table)
{
	table->cmd_table = 0;
	table->split_tokens = 0;
	table->tklist_head = 0;
	table->input = 0;
	table->tklist_size = 0;
}

void	quit(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}