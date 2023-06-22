/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:20:30 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/22 18:30:02 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	access_builtin(t_token *token)
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
