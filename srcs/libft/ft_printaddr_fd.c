/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printaddr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:54:02 by aselnet           #+#    #+#             */
/*   Updated: 2022/09/20 19:02:54 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_addr_to_hex(unsigned long long value, int fd)
{
	int		i;
	int		count;
	char	buff[16];

	i = 0;
	count = 0;
	while (i < 16)
	{
		if (value % 16 >= 10)
			buff[i] = ('a' + value % 16 % 10);
		else
			buff[i] = ('0' + value % 16);
		value /= 16;
		i++;
	}
	i--;
	while (buff[i] == '0' && i > -1)
		i--;
	while (i > -1)
	{
		count += ft_putchar_fd(buff[i], fd);
		i--;
	}
	return (count);
}

int	ft_printaddr_fd(unsigned long long value, int fd)
{
	int					count;

	if (!value)
	{
		write(1, "(nil)", 5);
		count = 5;
		return (count);
	}
	write(1, "0x", 2);
	count = 2;
	count += ft_addr_to_hex(value, fd);
	return (count);
}

/*#include <stdio.h>
int	main(void)
{
	void	*data;
	long unsigned	int	u;
	int		i;
	char	s;
	

	i = 0;
	data = &s;
	u = (long unsigned int)data;
	printf("my print address returns :\n");
	ft_printaddr_fd(u, 1);
	ft_putchar_fd('\n', 1);
	printf("printf %%p returns :\n%p\n", data);
}*/