/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:52:26 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/04 10:56:11 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_all_digits(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return (0);
}

void	ft_error_numeric(char *builtin, char *identifier)
{
	write(2, builtin, ft_strlen(builtin));
	write(2, ": ", 2);
	write(2, identifier, ft_strlen(identifier));
	write(2, ": numeric argument required\n", 28);
	g_minishell.exit_status = 1;
}

int	ft_check_numeric_arg(char **argv, int inside_pipe)
{
	if (ft_check_all_digits(argv[1]) == -1)
	{
		if (inside_pipe != 1)
			write(2, "exit\n", 5);
		ft_error_numeric("exit", argv[1]);
		g_minishell.exit_status = 2;
		if (inside_pipe != 1)
			ft_exit_utils(2, 1);
		return (-1);
	}
	return (0);
}
