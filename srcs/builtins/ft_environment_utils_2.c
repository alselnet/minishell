/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:56:46 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/05 16:40:20 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_env(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == 0 && s2[i] == '=')
		return (0);
	if (s1[i] == '=' && s2[i] == 0)
		return (0);
	if (s1[i] == '=' && s2[i] != '=')
		return (-1);
	if (s2[i] == '=' && s1[i] != '=')
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_compute_env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**ft_strdup_env(char **envp)
{
	int		size;
	char	**env;
	int		i;

	size = ft_compute_env_len(envp);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (env[i] == NULL)
		{
			ft_free_env(env, i);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}
