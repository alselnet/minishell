/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/22 00:54:34 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

//MODIFY PWD and OLDPWD (if OLDPWD does not exist, create one. Everytime you cd change PWD)
/*
method:
unset OLDPWD (if it does not exist, nothing happens)
recreate OLDPWD
change PWD
*/

// note: cd at home or at the cwd when we started minishell?

void	ft_cd(int argc, char **argv)
{
	char *new_path;
	char print_path[1000];
	
	// cd without a path
	if (argc == 2)
	{
		new_path = getenv("HOME");
		if (new_path == NULL)
			ft_error("cd $HOME failed");
		if (chdir(new_path) != 0)
			ft_error("cd $HOME failed");
	}
	// cd with a relative or absolute path
	else
	{
		if (chdir(argv[2]) != 0)
			ft_error("cd to new directory failed");
	}
	// Check that we get the right directory now	
	getcwd(print_path, sizeof(print_path));
	printf("%s\n", print_path);
}