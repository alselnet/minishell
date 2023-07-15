// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_exit.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/06/11 18:03:41 by orazafy           #+#    #+#             */
// /*   Updated: 2023/07/15 16:31:55 by orazafy          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// unsigned char	ft_atoi_exit(char *str)
// {
// 	int	nb;
// 	int	i;

// 	if (*str == '+' || *str == '-')
// 		str++;
// 	i = 1;
// 	nb = str[0] % '0';
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		nb = (nb * 10) + (str[i] % '0');
// 		i++;
// 	}
// 	return (nb);
// }

// void	ft_exit(int argc, char **argv)
// {
// 	if (argc > 2)
// 	{
// 		if (ft_check_numeric_arg(argv) != -1)
// 		{
// 			if (g_minishell.cmd.inside_pipe != 1)
// 				write(2, "exit\n", 5);
// 			write(2, "exit: too many arguments\n", 25);
// 			if (g_minishell.cmd.inside_pipe == 1)
// 				ft_exit_utils(1, 1);
// 			if (g_minishell.status_done == 0 && g_minishell.cmd.final_cmd == 1)
// 			{
// 				g_mini.exit_status = 1;
// 				g_minishell.status_done = 1;
// 			}	
// 		}
// 	}
// 	else if (argc == 1)
// 		ft_exit_utils(g_mini.exit_status, 0);
// 	else
// 	{
// 		if (ft_check_numeric_arg(argv) != -1)
// 			ft_exit_utils(ft_atoi_exit(argv[1]), 0);
// 	}
// }
