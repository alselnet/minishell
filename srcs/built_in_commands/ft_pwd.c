/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:53 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/23 19:56:55 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

void	ft_pwd(void)
{
	char current_path[1000];
	char *cwd;
		
	cwd = getcwd(current_path, sizeof(current_path));
	if (cwd == NULL)
	{
		perror("");
		return ;
	}
	printf("%s\n", current_path);
}