/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:37:43 by aselnet           #+#    #+#             */
/*   Updated: 2022/09/20 19:02:49 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print(char c, va_list args, int *count)
{
	if (c == '%')
		*count += ft_putchar_fd('%', 1);
	else if (c == 'c')
		*count += ft_putchar_fd(va_arg(args, int), 1);
	else if (c == 's')
		*count += ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'p')
		*count += ft_printaddr_fd(va_arg(args, unsigned long long), 1);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(args, int), 1, count);
	else if (c == 'u')
		ft_putunsigned_fd(va_arg(args, unsigned int), 1, count);
	else if (c == 'x')
		*count += ft_put_lower_hex_fd((unsigned long int)
				va_arg(args, unsigned int), 1);
	else if (c == 'X')
		*count += ft_put_upper_hex_fd((unsigned long int)
				va_arg(args, unsigned int), 1);
	else
	{
		*count += ft_putchar_fd('%', 1);
		*count += ft_putchar_fd(c, 1);
	}
	return ;
}

int	ft_printf(char const *s, ...)
{
	int		i;
	int		count;
	va_list	args;

	if (!s)
		return (-1);
	va_start(args, s);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			print (s[i], args, &count);
		}
		else
			count += ft_putchar_fd(s[i], 1);
		if (s[i])
			i++;
	}
	va_end(args);
	return (count);
}

/*#include <limits.h>
int	main (void)
{
	int	i = 0;
	int	j = 0;
	
	i = ft_printf(" hehehe%Qheheheh ", LONG_MIN);
	j = printf(" hehehe%Qheheheh ", LONG_MIN);

	ft_printf("\nft_printf returns %d\n", i);
	printf("\nprintf returns %d\n", j);

	//printf("Hello everyone this is test %d for ft_printf %d\n", i, j);
	return (0);
}*/