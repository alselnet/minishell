/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 22:59:24 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/25 17:57:52 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct s_data_env
{
	int		size;
	char	**envp;
}				t_data_env;

typedef struct s_minishell
{
	int	exit_status;
}				t_minishell;

extern t_minishell	g_minishell;

// ft_builtins_utils.c 
void	ft_error_identifier(char *builtin, char *identifier);
void	ft_error(char *error_msg, t_data_env *s_data_env);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

// ft_builtins_utils_2.c
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_srch(char const c, char const *str);
char	*ft_strjoin(char const *s1, char const *s2);

// ft_cd.c
void	ft_error_file(char *builtin, char *file);
int		ft_cd_without_arg(char **argv);
void	ft_cd(int argc, char **argv, t_data_env *s_data_env);

// ft_cd_utils.c
int		ft_update_oldpwd_utils(t_data_env *s_data_env, char *oldpwd);
int		ft_update_oldpwd(t_data_env *s_data_env);
void	ft_update_pwd(char *pwd, t_data_env *s_data_env);
char	*ft_get_pwd(t_data_env *s_data_env);

// ft_echo.c
int		ft_check_option(char *str);
void	ft_echo(int argc, char **argv);

// ft_env.c
void	ft_env(char **envp);

// ft_environment_utils_2.c 
int		ft_strcmp_env(const char *s1, const char *s2);
int		ft_compute_env_len(char **envp);
char	**ft_strdup_env(char **envp);

// ft_environment_utils.c
int		ft_remove_var_in_env(int i, t_data_env *s_data_env);
char	**ft_add_var_env(t_data_env *s_data_env, char *new_var);
void	ft_free_env(char **env, int size);

// ft_export_utils.c
void	ft_print_export(char *str);
void	ft_get_env_min(char **min, int *pos_min, int size, char **env);
int		ft_print_env_min(char **env, int size);
int		ft_check_var_format_export(char **argv, int *j);

// ft_export.c
void	ft_export_without_arg(t_data_env *s_data_env);
void	ft_export_with_arguments(char **argv, t_data_env *s_data_env, int j);
void	ft_export(int argc, char **argv, t_data_env *s_data_env);

// ft_pwd.c
void	ft_pwd(void);

// ft_unset.c
void	ft_unset_without_arg(t_data_env *s_data_env);
int		ft_check_var_format_unset(char **argv, int *j);
int		ft_unset_with_arg(char **argv, t_data_env *s_data_env, int j);
void	ft_unset(int argc, char **argv, t_data_env *s_data_env);

#endif