/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:42:18 by aselnet           #+#    #+#             */
/*   Updated: 2022/09/20 19:02:44 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putunsigned_fd(unsigned int n, int fd, int *count)
{
	char				c;

	if (n / 10)
		ft_putunsigned_fd((n / 10), fd, count);
	c = (n % 10 + '0');
	*count += ft_putchar_fd(c, 1);
}
/*int	main()
{
	int n = -2147483648;
	ft_putnbr_fd(n, 2);
	return (0);
}*/