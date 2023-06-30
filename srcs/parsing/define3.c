/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:20:30 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/30 13:57:39 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_token *token)
{
	if (ft_strcmp("cd", token->content) == 0)
		return (0);
	else if (ft_strcmp("pwd", token->content) == 0)
		return (0);
	else if (ft_strcmp("unset", token->content) == 0)
		return (0);
	else if (ft_strcmp("env", token->content) == 0)
		return (0);
	else if (ft_strcmp("export", token->content) == 0)
		return (0);
	else if (ft_strcmp("echo", token->content) == 0)
		return (0);
	else if (ft_strcmp("exit", token->content) == 0)
		return (0);
	return (1);
}

int	check_path(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (0);
	}
	return (1);
}
