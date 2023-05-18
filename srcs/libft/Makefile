# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/02 15:46:29 by aselnet           #+#    #+#              #
#    Updated: 2023/04/06 11:40:32 by aselnet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -D BUFFER_SIZE=32
SRCS = ft_printaddr_fd.c\
ft_printf.c\
ft_put_lower_hex_fd.c\
ft_put_upper_hex_fd.c\
ft_putchar_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_putunsigned_fd.c\
ft_split.c\
ft_substr.c\
ft_strjoin.c\
ft_strlen.c\
ft_strlcpy.c\
ft_strncmp.c\
ft_strnstr.c\
get_next_line.c\
get_next_line_utils.c\


OBJS = ${SRCS:.c=.o}

BONUSOBJS = ${BONUS:.c=.o}
LIB = ar rcs
REMOVE = rm -f

$(NAME): ${OBJS}
		${LIB} $(NAME) ${OBJS} 
		mv ${NAME} ../../		
	
bonus: ${BONUSOBJS}
		${LIB} $(NAME) ${BONUSOBJS}

all:$(NAME)

clean :
		${REMOVE} ${OBJS} ${BONUSOBJS}

fclean :clean
		${REMOVE} ../$(NAME)

re:fclean all

.PHONY: all clean fclean bonus re libft.a