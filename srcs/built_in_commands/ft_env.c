/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:06:31 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/22 00:42:48 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

void ft_env(char **envp)
{
	int	i;
	
	// maybe use ft_print_env in the future
	i = 0;
	while(envp[i])
		printf("%s\n", envp[i++]);
}