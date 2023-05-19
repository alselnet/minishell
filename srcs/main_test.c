/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/19 14:52:55 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	token_testing(void)
{
	t_token	*head;
	t_token	*token;
	t_token	*last;
	char	*content;

	content = ft_calloc(sizeof(char), 2);
	content[0] = 'z';
	create_token_list(25);
	token = tk_new(content);
	tk_addto(&head, token, 25);

	printf("initial print\n\n");
	print_token_list(&head);
	printf("%d tokens\n", tk_size(head));

	tk_moveto(&head, token, 15);

	printf("after moving token\n\n");
	print_token_list(&head);
	printf("%d tokens\n", tk_size(head));

	last = tk_last(head);
	printf("reverse print\n\n");
	rev_print_token_list(&last, &head);
	printf("%d tokens\n", tk_size(head));

	tk_clear(&head);
} */

int	main (int argc, char **argv)
{
	t_lexing	ltable;
	//token_testing();
	(void)argv;
	init_table(&ltable);
	if (argc != 1)
	{
		printf("./minishell doesn't take any arguments\n");
		return (0);
	}
	while(1)
	{
		ltable.input = readline("> ");
		if (!ltable.input || !ltable.input[0])
			return (printf("exit\n"));
		create_token_list(&ltable);
		print_token_list(ltable.tklist_head);
		tk_clear(ltable.tklist_head);
		free(ltable.input);
	}
	return (0);
}
