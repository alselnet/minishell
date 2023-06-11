/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:03:41 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/11 20:40:10 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_to_int(char *str)
{
	int	nb;
	int	i;

	i = 1;
	nb = str[0] % '0';
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] % '0');
		i++;
	}
	// if (i != ft_strlen(str))
	//
	return (nb);
}

int	ft_atoi_exit(char *str)
{
	// if ((*str < '0' || *str > '9') && (*str != '+'))
	// 	
	if (*str == '+')
	{
		str++;
		// if (*str < '0' || *str > '9')
		//
	}
	return (ft_char_to_int(str));
}

void	ft_exit_utils(int status)
{
	if (dup2(g_minishell.data_env.stdin, STDIN_FILENO) == -1)
		ft_error(1);
	if (dup2(g_minishell.data_env.stdout, STDOUT_FILENO) == -1)
		ft_error(1);
	printf("exit\n");
	ft_close_all_fds();
	ft_free_cmd(&g_minishell.cmd);
	ft_free_env(g_minishell.data_env.envp, g_minishell.data_env.size);
	tk_clear(&g_minishell.ltable.tklist_head);
	free(g_minishell.ltable.input);
	rl_clear_history();
	exit(status);
}
// tous le bash ne se comportent pas de la même manière. 

// il faut gérer le cas d'un status non numérique
// certains bashs quand il y a un argument non numérique 'exit "sdkjsld"', il donne un message d'erreur
// sur ubuntu bash, il m'exit quand meme mais je sais pas le status donné, (0 ?)

// Si le status est trop grand (c'est quoi trop grand ? int ? long ? long long ?), quel sera le status ?
// je fais quoi des négatifs ?
// // // // -> après réflexion, je crois ca fait le tour d'un int

// est ce que +2, c'est non num, ou num ?

void	ft_exit(int	argc, char **argv)
{
	if (argc > 2)
	{
		write(1, "exit\n", 5);
		write(2, "exit: too many arguments\n", 25);
		g_minishell.exit_status = 1;
	}
	else if (argc == 1)
		ft_exit_utils(g_minishell.exit_status);
	else
	// à gérer le cas si l'argument est non numérique
		ft_exit_utils(ft_atoi_exit(argv[1]));
}