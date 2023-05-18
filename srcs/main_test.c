/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 18:10:08 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main ()
{
	t_token	*head;
	t_token	*token;
	char	*content;

	content = ft_calloc(sizeof(char), 2);
	content[0] = 'z';
	head = create_token_list(25);
	token = tk_new(content);
	tk_addto(&head, token, 25);

	printf("initial print\n\n");
	print_token_list(&head);
	printf("%d tokens\n", tk_size(head));

	tk_moveto(&head, token, 15);

	printf("after moving token\n\n");
	print_token_list(&head);
	printf("%d tokens\n", tk_size(head));

	tk_clear(&head);
	return (0);
}
