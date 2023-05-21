/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:08:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/22 00:47:17 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

void	ft_print_export(char *str)
{
	while (*str != '=')
	{
		printf("%c", *str);
		str++;
	}
	printf("%c", *str);
	str++;
	printf("\"");
	while (*str)
	{
		printf("%c", *str);
		str++;
	}
	printf("\"");
	printf("\n");
}

int ft_print_env_min(char **env, int size)
{
	int	i;
	char *min;
	int	pos_min;

	i = 0;
	while (i < size)
	{
		if (env[i] != NULL)
		{
			min = env[i];
			pos_min = i;
			break ;
		}
		i++;
	}
	i = 0;
	while(i < size)
	{
		if (env[i] == NULL)
		{
			i++;
			continue ;
		}
		if (ft_strcmp_env(env[i], min) < 0)
		{
			min = env[i];
			pos_min = i;
		}	
		i++;
	}
	printf("declare -x ");
	ft_print_export(min);
	return(pos_min);
}

void	ft_export_without_arg(t_data_env *s_data_env)
{
	int	i;
	char **dup_env;
	int min;
	
	dup_env = ft_strdup_env(s_data_env->envp);
	i = 0;
	while (i < s_data_env->size)
	{
		min = ft_print_env_min(dup_env, s_data_env->size);
		free(dup_env[min]);
		dup_env[min] = NULL;
		i++;
	}
	free(dup_env[i]);
	free(dup_env);
}

// ERROR CASES TO HANDLE
/*
> check for reserved word ?

> export/unset will handle multiple arguments in a row (like as long as it's a WORD, it's echo arguments)

> This error will have to be handled
$ export mama=PAPA mam-rm=rl
bash: export: `mam-rm=rl': not a valid identifier
$ env | grep mama
mama=PAPA

> if the variable does exist, only update its value
don't add a new line

>  TAKE THIS INTO ACCOUNT: (need a history)
$papa=mama
$export papa

> variable can have accent ? like é è etc

=> SAME FOR UNSET!!!!
*/
void ft_export(int argc, char **argv, t_data_env *s_data_env)
{
	char **dup_env;
	int i;
	
	(void)argv;
	// export without any argument
	if (argc == 2)
	{
		ft_export_without_arg(s_data_env);
		return ;
	}
	// export with an argument
	// Check that the variable identifier has a correct format
	if (ft_srch('=', argv[2]) == 0)
	{
		printf("export: '%s': not a valid identifier\n", argv[2]);
		return ;
	}
	i = 0;
	while (argv[2][i] && argv[2][i] != '=')
	{
		if (ft_isalnum(argv[2][i]) == 0)
		{
			printf("export: '%s': not a valid identifier\n", argv[2]);
			return ;
		}
		i++;
	}
	// the argument must have a '=' at least at the 2nd character
	if (ft_srch('=', argv[2]) >= 1)
	{
		//il faudra créer une fonction: dup_env = ft_add_var_env(char **envp, char *new_var)
		i = 0;
		dup_env = (char **)malloc(sizeof(char *) * (s_data_env->size + 2));
		while (s_data_env->envp[i])
		{
			dup_env[i] = ft_strdup(s_data_env->envp[i]);
			i++;
		}
		dup_env[i++] = ft_strdup(argv[2]);
		dup_env[i] = NULL;
		s_data_env->size = s_data_env->size++;
		s_data_env->envp = dup_env;
	}
}