# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:46:57 by aselnet           #+#    #+#              #
#    Updated: 2023/05/18 12:47:08 by aselnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -MMD -I include

SRC = srcs/

 
OBJS = ${SRC:.c=.o}
DEPS = ${SRC:.c=.d}

REMOVE = rm -f

${NAME}: ${OBJS}
		make -C srcs/libft
		$(CC) $(CFLAGS) ${OBJS} libft.a -o $(NAME)

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