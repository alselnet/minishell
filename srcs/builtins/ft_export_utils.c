/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:23:19 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/25 19:40:38 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_print_export(char *str)
{
	while (*str != '=')
		printf("%c", *(str++));
	printf("%c\"", *str);
	str++;
	while (*str)
		printf("%c", *(str++));
	printf("\"\n");
}

void	ft_get_env_min(char **min, int *pos_min, int size, char **env)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (env[i] != NULL)
		{
			*min = env[i];
			*pos_min = i;
			break ;
		}
		i++;
	}
}

int	ft_print_env_min(char **env, int size)
{
	int		i;
	char	*min;
	int		pos_min;

	ft_get_env_min(&min, &pos_min, size, env);
	i = 0;
	while (i < size)
	{
		if (env[i] == NULL)
		{
			i++;
			continue ;
		}
		if (ft_strcmp_env(env[i], min) < 0)
		{
			min = env[i];
			pos_min = i;
		}	
		i++;
	}
	printf("declare -x ");
	ft_print_export(min);
	return (pos_min);
}

int	ft_check_var_format_export(char **argv, int *j)
{
	int	i;

	if (ft_srch('=', argv[*j]) < 1)
	{
		ft_error_identifier("export", argv[*j]);
		g_minishell.exit_status = 1;
		(*j)++;
		return (-1);
	}
	i = 0;
	while (argv[*j][i] && argv[*j][i] != '=')
	{
		if (ft_isalnum(argv[*j][i]) == 0 && (argv[*j][i] != '_'))
		{
			ft_error_identifier("export", argv[*j]);
			g_minishell.exit_status = 1;
			(*j)++;
			return (-1);
		}
		i++;
	}
	return (0);
}
