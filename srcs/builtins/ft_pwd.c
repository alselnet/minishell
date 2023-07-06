/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:53 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/04 19:25:49 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_retrieve_pwd_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp_env("PWD=", envp[i]) == 0)
			break ;
		i++;
	}
	if (envp[i] != NULL)
		return (envp[i] + 4);
	else
		return (NULL);
}

void	ft_pwd(char **envp)
{
	char	current_path[1000];
	char	*cwd;
	char	*pwd;

	pwd = ft_retrieve_pwd_env(envp);
	if (pwd == NULL)
	{
		cwd = getcwd(current_path, sizeof(current_path));
		if (cwd == NULL)
		{
			perror("pwd: getcwd");
			ft_exit_utils(EXIT_FAILURE, 1);
		}
		printf("%s\n", current_path);
		ft_exit_utils(EXIT_SUCCESS, 1);
	}
	printf("%s\n", pwd);
	ft_exit_utils(EXIT_SUCCESS, 1);
}
