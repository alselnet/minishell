/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:30:15 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/19 17:39:24 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_table(t_lexing *ltable)
{
	ltable->tklist_head = 0;
	ltable->input = 0;
	ltable->tklist_size = 0;
}
