/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:53 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/21 23:05:30 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

void	ft_pwd(void)
{
	char print_path[1000];
	
	if (chdir("./") != 0)
		ft_error("getting current directory failed");
	// Check that we get the right directory now	
	getcwd(print_path, sizeof(print_path));
	printf("%s\n", print_path);
}