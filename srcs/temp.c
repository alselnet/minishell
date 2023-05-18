#include "../include/minishell.h"

void	print_token_list(t_token **head)
{
t_token	*browse;
int	i;

i = 0;
if (!head || !*head)
	return ;

browse = *head;
while (browse)
{
	printf("token %d contains %s\n", i, browse->content);
	browse = browse->next;
	i++;
}
}


t_token	*	create_token_list(int	number_of_tokens)
{
	t_token	*head;
	t_token	*token;
	char	**contents;
	int		i;

	i = 0;	
	contents = ft_calloc(sizeof(char *), number_of_tokens + 1);
	contents[0] = ft_calloc (sizeof(char), 2);
	contents[0][0] = 'a' + i;
	head = tk_new(contents[0]);
	while (++i < number_of_tokens)
	{
		contents[i] = ft_calloc (sizeof(char), 2);
		contents[i][0] = 'a' + i;
		token = tk_new(contents[i]);
		tk_add_back(&head, token);
	}
	free(contents);
	return (head);
}
