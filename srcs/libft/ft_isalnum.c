/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:58:04 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/19 19:44:51 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c < 123 && c > 96) || (c < 91 && c > 64) || (c < 58 && c > 47))
		return (1);
	else if (c == 95)
		return (1);
	return (0);
}
/*int main()
{
    char    c;
	int	i;

    printf("Please enter a character :\n");
    scanf("%c", &c);
    i = ft_isalnum(c);
    printf("ft_isalnum returns %d\n", i);
    return (0);
}*/