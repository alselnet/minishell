/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:09:34 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/06 17:33:03 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_builtin_with_stdout(void)
{
	if (dup2(g_minishell.data_env.stdin, STDIN_FILENO) == -1)
		ft_error(1);
	close(g_minishell.data_env.stdin);
	if (dup2(g_minishell.data_env.stdout, STDOUT_FILENO) == -1)
		ft_error(1);
	close(g_minishell.data_env.stdout);
	exit(EXIT_SUCCESS);
}

void	ft_error_identifier(char *builtin, char *identifier)
{
	write(2, builtin, ft_strlen(builtin));
	write(2, ": '", 3);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	while (s[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	j = 0;
	while (s[j])
	{
		dest[j] = s[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}
