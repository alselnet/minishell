# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 15:46:29 by aselnet           #+#    #+#              #
#    Updated: 2023/07/06 02:23:28 by aselnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -D BUFFER_SIZE=32
SRCS = ft_calloc.c\
ft_isinbase.c\
ft_itoa.c\
ft_putstr_fd.c\
ft_realloc.c\
ft_split.c\
ft_substr.c\
ft_strdup.c\
ft_strenvcmp.c\
ft_strjoin.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strcmp.c\
ft_strmatch.c\
ft_strncmp.c\
ft_strnstr.c\
ft_strrev.c\
ft_strtrim.c\
get_next_line.c\
get_next_line_utils.c\


OBJS = ${SRCS:.c=.o}

BONUSOBJS = ${BONUS:.c=.o}
LIB = ar rcs
REMOVE = rm -f

$(NAME): ${OBJS}
		${LIB} $(NAME) ${OBJS} 		
	
bonus: ${BONUSOBJS}
		${LIB} $(NAME) ${BONUSOBJS}

all:$(NAME)

clean :
		${REMOVE} ${OBJS} ${BONUSOBJS}

fclean :clean
		${REMOVE} $(NAME)

re:fclean all

.PHONY: all clean fclean bonus re libft.a