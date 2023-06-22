/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:17:00 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/22 13:50:33 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_option(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			break ;
		str++;
	}
	if (*str != 0)
		return (0);
	return (1);
}

void	ft_echo(int argc, char **argv)
{
	int	i;
	int	has_option;

	has_option = 0;
	if (argc == 1)
	{
		printf("\n");
		return ;
	}
	has_option = ft_check_option(argv[1]);
	if ((argc == 2) && (has_option == 1))
		return ;
	if (has_option == 1)
		i = 2;
	else
		i = 1;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i++ != argc - 1)
			printf(" ");
	}
	if (has_option != 1)
		printf("\n");
	ft_exit_utils(EXIT_SUCCESS, 1);
}
