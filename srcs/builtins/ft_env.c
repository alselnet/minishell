// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_env.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/05/21 23:06:31 by orazafy           #+#    #+#             */
// /*   Updated: 2023/07/07 23:29:33 by orazafy          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// void	ft_env(char **envp, int argc)
// {
// 	int	i;

// 	if (argc > 1)
// 		ft_exit_utils(EXIT_SUCCESS, 1);
// 	else
// 	{
// 		i = 0;
// 		while (envp[i])
// 			printf("%s\n", envp[i++]);
// 		ft_exit_utils(EXIT_SUCCESS, 1);
// 	}
// }
