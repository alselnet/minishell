/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:17:00 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/23 19:24:01 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

// to test with an option -n, -nnnn -nnnnnnn. I type this string "./a.out echo option" (option is for the real option)

void	ft_echo(int argc, char **argv)
{
	int i;
	
	// echo without an option, and without arguments
	if (argc == 2)
	{
		printf("\n");
		return ;
	}
	// echo with option, but no arguments
	if ((argc == 3) && (ft_strcmp(argv[2], "option") == 0))
		return ;
	
	// initalize i depending on the presence of an option
	if (ft_strcmp(argv[2], "option") == 0)
		i = 3;
	else
		i = 2;
	// Loop through all the strings
	while (i < argc)
	{
		// while it's not an option
		if (ft_strcmp(argv[i], "option") != 0)
			printf("%s", argv[i]);
		// if it's the last string, no space
		if (i != argc - 1)
			printf(" ");
		i++;
	}
	// if there is no option
	if (ft_strcmp(argv[2], "option") != 0)
		printf("\n");
}