/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_upper_hex_fd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:36:42 by aselnet           #+#    #+#             */
/*   Updated: 2022/09/20 19:02:38 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_upper_hex_fd(unsigned long int value, int fd)
{
	int		i;
	int		count;
	char	buff[8];

	i = -1;
	count = 0;
	if (value < 1)
		count += ft_putchar_fd('0', fd);
	if (value < 1)
		return (count);
	while (++i < 8)
	{
		if (value % 16 >= 10)
			buff[i] = ('A' + value % 16 % 10);
		else
			buff[i] = ('0' + value % 16);
		value /= 16;
	}
	i--;
	while (buff[i] == '0' && i > -1)
		i--;
	i++;
	while (--i > -1)
		count += ft_putchar_fd(buff[i], fd);
	return (count);
}
/*#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char** argv)
{
	if (argc != 2)
		return (0);
	unsigned long long u;
	u = atoi(argv[1]);
	ft_put_upper_hex_fd(u, 1);
	printf("\n%X\n", u);
	return (0);
}*/