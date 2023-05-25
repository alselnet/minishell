/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:09:34 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/25 18:12:58 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_error_identifier(char *builtin, char *identifier)
{
	write(2, builtin, ft_strlen(builtin));
	write(2, ": '", 3);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n", 26);
}

void	ft_error(char *error_msg, t_data_env *s_data_env)
{
	perror(error_msg);
	ft_free_env(s_data_env->envp, s_data_env->size);
	g_minishell.exit_status = 1;
	exit(EXIT_FAILURE);
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
