/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:01:36 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/18 19:13:56 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//////////// BUILT-IN COMMANDS UTILITIES ////////////
void	ft_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!n)
		return (0);
	while ((i < n - 1) && (s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// int	ft_compute_env_len(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	return(i);
// }

void	ft_remove_var_in_env(int i, char **envp)
{
	while (1)
	{
		envp[i] = envp[i + 1];
		if (envp[i] == NULL)
			break ;
		i++;
	}
}
////////////////////////////////////////////////


/////////////// BUILT-IN COMMANDS ///////////////////
void	ft_pwd(void)
{
	char print_path[1000];
	
	if (chdir("./") != 0)
		ft_error("getting current directory failed");
	// Check that we get the right directory now	
	getcwd(print_path, sizeof(print_path));
	printf("%s\n", print_path);
}

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

void ft_unset(int argc, char **argv, char **envp)
{
	int i;
	int var_len;

	i= 0;
	// unset command without argument remove all the environment variables
	if (argc == 2)
	{
		while (envp[i])
			envp[i++] = NULL;
	}
	// unset command with a argument, remove only the variable mentionned in the argument
	else
	{
		var_len = ft_strlen(argv[2]);
		while (envp[i])
		{
			if (ft_strncmp(argv[2], envp[i], var_len) == 0)
				break ;
			i++;
		}
		if (envp[i] == NULL)
			printf("unset: '%s': not a valid identifier\n", argv[2]);
		else
			ft_remove_var_in_env(i, envp);
	}
	// Check that the variable(s) has been removed 
	if (envp[i] == NULL)
		return ;
	i = 0;
	while(envp[i])
		printf("%s\n", envp[i++]);
}

void ft_env(char **envp)
{
	int	i;
	
	i = 0;
	while(envp[i])
		printf("%s\n", envp[i++]);
}

int	main (int argc, char **argv, char **envp)
{
	if (ft_strcmp("cd", argv[1]) == 0)
		ft_cd(argc, argv);
	else if (ft_strcmp("pwd", argv[1]) == 0)
		ft_pwd();
	else if (ft_strcmp("unset", argv[1]) == 0)
		ft_unset(argc, argv, envp);
	else if (ft_strcmp("env", argv[1]) == 0)
		ft_env(envp);
	return (0);
}