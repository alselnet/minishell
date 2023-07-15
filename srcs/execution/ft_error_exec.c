/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:25:18 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 17:35:57 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_no_such_file(char *file)
{
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}

void	ft_error_cmd_not_found(t_minishell *mini)
{
	write(2, mini->cmd.first_arg, ft_strlen(mini->cmd.first_arg));
	write(2, ": command not found\n", 20);
	ft_exit_exec(127, mini);
}

void	ft_error(int status, t_minishell *mini)
{
	perror("");
	ft_free_all_exec(mini);
	exit(status);
}
