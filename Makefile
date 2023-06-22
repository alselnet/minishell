# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:46:57 by aselnet           #+#    #+#              #
#    Updated: 2023/06/22 15:55:02 by aselnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = clang
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -g -I include

SRC = srcs/expand.c\
srcs/expand2.c\
srcs/define.c\
srcs/define2.c\
srcs/minishell.c\
srcs/tokens.c\
srcs/tokens2.c\
srcs/init.c\
srcs/quit.c\
srcs/lexing.c\
srcs/parsing.c\
srcs/temp.c\
srcs/ft_environment_var_utils.c\

 
OBJS = ${SRC:.c=.o}
DEPS = ${SRC:.c=.d}

REMOVE = rm -f

${NAME}: ${OBJS}
		make -C srcs/libft
		$(CC) $(CFLAGS) ${OBJS} libft.a -lreadline -o $(NAME)

-include $(DEPS)

all:${NAME}

clean : 
		make clean -C srcs/libft
		${REMOVE} ${DEPS} ${OBJS} ${DEPS_BONUS}

fclean : 
		make fclean -C srcs/libft
		${REMOVE} libft.a
		${REMOVE} ${DEPS} ${OBJS} ${DEPS_BONUS} $(NAME)

re: fclean all

re_b: fclean

.PHONY: all clean fclean re