/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:30:15 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/30 16:27:02 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_table(t_lexing *ltable)
{
	ltable->tklist_head = 0;
	ltable->input = 0;
	ltable->tklist_size = 0;
}
