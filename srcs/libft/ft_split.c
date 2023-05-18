/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:06:15 by aselnet           #+#    #+#             */
/*   Updated: 2022/05/06 18:23:16 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_make_a_split(char const *s, size_t size)
{
	unsigned int	i;
	char			*split;

	i = 0;
	split = (char *) malloc(size + 1);
	if (!split)
		return (0);
	while (i < size)
	{
		split[i] = s[i];
		i++;
	}
	split[i] = 0;
	return (split);
}

int	ft_strslen(char const *s, int c)
{
	int	slen;
	int	i;
	int	j;

	slen = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			j++;
		}
		if (j)
			slen++;
	}
	return (slen);
}

/*void	clear_tab(char **split_tab, unsigned int n)
{
	unsigned int	i;

	i = -1;
	while (++i < n)
		free(split_tab[n]);
}*/

char	**ft_split(char const *s, char c)
{
	char				**split_tab;
	unsigned int		i;
	unsigned int		j;
	unsigned int		n;

	split_tab = (char **) malloc((ft_strslen(s, c) + 1) * sizeof(char *));
	if (!split_tab)
		return (0);
	i = 0;
	n = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i + j] && s[i + j] != c)
			j++;
		i += j;
		if (j)
			split_tab[++n] = ft_make_a_split(s + i - j, j);
	}
	split_tab[++n] = 0;
	return (split_tab);
}
/*#include <stdio.h>
int	main()
{
	char**	split_tab;
	int	i;

	i = 0;
	char string[] = "";
	split_tab = ft_split(string, ' ');
	if (!split_tab)
		return (0);
	printf("ft_strslen returns: %d\n", ft_strslen(string, ' '));
	printf("processing the following string : %s\n", string);
	while (split_tab[i])
	{
		printf("%s\n", split_tab[i]);
		i++;
	}
	while (split_tab[i])
	{
		free(split_tab[i]);
		i++;
	}
	free(split_tab);
	return (0);
}*/