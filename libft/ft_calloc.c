/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 18:03:42 by aselnet           #+#    #+#             */
/*   Updated: 2022/05/06 17:57:24 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (size && count > (size_t) -1 / size)
		return (0);
	result = (void *)malloc (count * size);
	if (!result)
		return (0);
	ft_bzero (result, count * size);
	return (result);
}
/*#include <stdint.h>
int	main()
{
	void	*result;

	result = ft_calloc(SIZE_MAX, SIZE_MAX);
	if (!result)
		return(0);
	printf("calloc allocated an array at address %p\n", result);
	free(result);
	return (0);
}*/