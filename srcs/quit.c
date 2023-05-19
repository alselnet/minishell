/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:41:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/19 18:11:11 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	quit(t_lexing *ltable, char *error_msg,	char mode)
{
	if (mode == 1)
		tk_clear(&ltable->tklist_head);
	perror(error_msg);
	exit(EXIT_FAILURE);
}