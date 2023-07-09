/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 20:49:08 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/09 21:05:38 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_shlvl(t_data_env *data_env, int pos)
{
	char	*str_nb;
	int		nb;
	char	**env;

	env = data_env->envp;
	str_nb = env[pos] + 6;
	nb = ft_char_to_int(str_nb);
	nb++;
	str_nb = ft_itoa(nb);
	if (str_nb == NULL)
		ft_error(1);
	free(env[pos]);
	env[pos] = NULL;
	env[pos] = ft_strjoin("SHLVL=", str_nb);
	if (env[pos] == NULL)
	{
		free(str_nb);
		ft_error(1);
	}	
	free(str_nb);
}

int	ft_check_minishell_cmd(char *str)
{
	int	pos_mini;

	pos_mini = ft_strlen(str) - 9;
	if (pos_mini < 0)
		return (0);
	if (ft_strcmp(&str[pos_mini], "minishell") == 0)
		return (1);
	return (0);
}

int	ft_search_shlvl_env(t_data_env *data_env)
{
	int	i;

	i = 0;
	while (data_env->envp[i])
	{
		if (ft_strcmp_env("SHLVL=", data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (data_env->envp[i] != NULL)
		return (i);
	return (-1);
}
