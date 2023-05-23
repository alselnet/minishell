/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:50:58 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/23 18:51:34 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_variable_value(char **env)
{
	char	*full_var;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full_var = *env;
	while (full_var[i] && full_var[i] != '=')
		i++;
	if (!full_var[i])
		return (0);
	j += i + 1;
	while (full_var[j] && full_var[j] != '\n')
		j++;
	if (j < 1)
		return (0);
	value = ft_substr(*env + i + 1, 0, j);
	if (!value)
		return (0);
	return (value);
}
