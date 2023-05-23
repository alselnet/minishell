/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_commands.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:59:24 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/23 19:56:44 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_COMMANDS_H
# define BUILT_IN_COMMANDS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_data_env
{
	int		size;
	char	**envp;
}				t_data_env;

// ft_built_in_commands_utils.c 
void	ft_error(char *error_msg, t_data_env *s_data_env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_srch(char const c, char const *str);
char	*ft_strjoin(char const *s1, char const *s2);

// ft_cd.c
void	ft_cd(int argc, char **argv, t_data_env *s_data_env);

// ft_env.c
void	ft_env(char **envp);

// ft_environment_var_utils.c 
int		ft_strcmp_env(const char *s1, const char *s2);
int		ft_compute_env_len(char **envp);
void	ft_remove_var_in_env(int i, t_data_env *s_data_env);
char	**ft_strdup_env(char **envp);
void	ft_print_env(t_data_env *s_data_env);
void	ft_free_env(char **env, int size);
char	**ft_add_var_env(t_data_env *s_data_env, char *new_var);

// ft_export.c
void	ft_print_export(char *str);
int 	ft_print_env_min(char **env, int size);
void	ft_export_without_arg(t_data_env *s_data_env);
void 	ft_export(int argc, char **argv, t_data_env *s_data_env);

// ft_pwd.c
void	ft_pwd(void);

// ft_unset.c
void ft_unset(int argc, char **argv, t_data_env *s_data_env);

// ft_echo.c
void	ft_echo(int argc, char **argv);

#endif