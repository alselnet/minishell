/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:48:31 by aselnet           #+#    #+#             */
/*   Updated: 2022/09/20 19:08:06 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (!s)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	while (s[++i])
	{
		write (fd, s + i, 1);
		count ++;
	}
	return (count);
}
/*int	main()
{
	char s[] = "salut a tous les ptizamis";
	ft_putstr_fd(s, 2);
	return (0);
}*/