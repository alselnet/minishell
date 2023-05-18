/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:50:52 by aselnet           #+#    #+#             */
/*   Updated: 2022/09/20 19:08:01 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd, int *count)
{
	char		c;
	long long	nb;

	nb = n;
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb = -nb;
		*count += 1;
	}
	if (nb / 10)
		ft_putnbr_fd((nb / 10), fd, count);
	c = (nb % 10 + '0');
	*count += ft_putchar_fd(c, 1);
}
/*int	main()
{
	int n = -2147483648;
	ft_putnbr_fd(n, 2);
	return (0);
}*/