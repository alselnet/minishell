/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:53 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/05 18:11:31 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	current_path[1000];
	char	*cwd;

	cwd = getcwd(current_path, sizeof(current_path));
	if (cwd == NULL)
	{
		perror("");
		ft_error(2);
	}
	printf("%s\n", current_path);
	exit(EXIT_SUCCESS);
}
