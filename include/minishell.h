/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:58:33 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/22 19:44:37 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../srcs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

//ENV
typedef struct s_data_env
{
	int		size;
	char	**envp;
}	t_data_env;

char	**ft_strdup_env(char **envp);
void	ft_print_env(t_data_env *s_data_env);
void	ft_remove_var_in_env(int i, t_data_env *s_data_env);\
int		ft_compute_env_len(char **envp);
int		ft_strcmp_env(const char *s1, const char *s2);

//PARSING & INDEXING
typedef struct s_token //liste doublement chainée contenant deux variables
{
	char			*content;
	char			*type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef	struct s_lexing
{
	t_token	*tklist_head;
	char	*input;
	int		tklist_size;
}	t_lexing;

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
void	rev_print_token_list(t_token **last, t_token **head);

//UTILS
void	init_table(t_lexing *table);
int		free_array(char **arr);
void	quit(t_lexing *ltable, char *error_msg,	char mode);

//PARSING
void	create_token_list(t_lexing *table);
void	expand_token_list(t_lexing *ltable, t_data_env *data_env);

#endif