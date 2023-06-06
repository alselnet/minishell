/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/05 17:42:34 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_file(char *builtin, char *file)
{
	write(2, builtin, ft_strlen(builtin));
	write(2, ": ", 2);
	write(2, file, ft_strlen(file));
	write(2, ": No such file or directory\n", 28);
}

int	ft_cd_without_arg(char **argv)
{
	char	*new_path;

	new_path = getenv("HOME");
	if (new_path == NULL)
	{
		perror("");
		g_minishell.exit_status = 1;
		return (-1);
	}
	if (chdir(new_path) != 0)
	{
		ft_error_file("cd", argv[1]);
		g_minishell.exit_status = 1;
		return (-1);
	}	
	return (0);
}

void	ft_cd(int argc, char **argv, t_data_env *s_data_env)
{
	char	*pwd;

	if (ft_update_oldpwd(s_data_env) == -1)
		return ;
	if (argc == 1)
	{
		if (ft_cd_without_arg(argv) == -1)
			return ;
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			ft_error_file("cd", argv[1]);
			g_minishell.exit_status = 1;
			return ;
		}
	}
	pwd = ft_get_pwd();
	if (pwd == NULL)
		return ;
	ft_update_pwd(pwd, s_data_env);
	g_minishell.exit_status = 0;
}