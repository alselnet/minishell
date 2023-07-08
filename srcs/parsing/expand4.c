/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:02:29 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/08 16:06:31 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_content_end(char *new_content, char *content, int i, int j)
{
	while (*(content + i))
	{
		new_content[j] = content[i];
		i++;
		j++;
	}
}
