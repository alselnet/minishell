/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:58:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/18 18:04:29 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../srcs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

//LEXING
typedef	struct s_token //liste doublement chainée contenant deux variables
{
	char			*content;
	char			*type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

/*adapations de libft_bonus*/
t_token	*tk_new(char	*content);
int		tk_size(t_token *token);
t_token	*tk_last(t_token *token);
void	tk_add_back(t_token **head, t_token *new);
void	tk_delone(t_token *token);
void	tk_clear(t_token **head);

/*nouvelles fonctions*/
void	tk_deftype(t_token *token, char *type);
void	tk_addto(t_token **head, t_token *new, int pos);
void	tk_moveto(t_token	**head, t_token *token, int pos);

//fonctions temporaires de test
void	print_token_list(t_token **head);
t_token	*	create_token_list(int	number_of_tokens);

#endif