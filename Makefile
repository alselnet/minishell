# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:46:57 by aselnet           #+#    #+#              #
#    Updated: 2023/06/02 23:09:25 by orazafy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
IFLAGS = -I$(INCDIR) -I$(LIBDIR)
LFLAGS = -lreadline -L$(LIBDIR) -lft

SRCDIR = srcs
OBJDIR = objs
BINDIR = bin
INCDIR = include
LIBDIR = libft

EXECDIR = execution
PARSINGDIR = parsing

EXEC_FILES = ft_execute.c

PARSING_FILES = define.c \
		define2.c \
		expand.c \
		ft_environment_var_utils.c \
		init.c \
		lexing.c \
		parsing.c \
		quit.c \
		temp.c \
		tokens.c \
		tokens2.c \
		utils.c

EXEC = $(addprefix $(EXECDIR)/, $(EXEC_FILES))
PARSING = $(addprefix $(PARSINGDIR)/, $(PARSING_FILES))
SRCS = $(addprefix $(SRCDIR)/, minishell.c $(EXEC) $(PARSING))
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCS = $(INCDIR)/minishell.h

NAME = $(BINDIR)/minishell

RMR = rm -rf
MKDIR_P = mkdir -p

LIBFT = $(LIBDIR)/libft.a

all: $(NAME)

$(LIBFT):
	cd $(LIBDIR) && make re

$(NAME): $(OBJS) $(LIBFT) | $(BINDIR)
	$(CC) $(CFLAGS) $(OBJS) $(IFLAGS) $(LIBS) $(LFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS) | $(OBJDIR)
	$(MKDIR_P) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@ 

$(BINDIR):
	$(MKDIR_P) $(BINDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

clean:
		$(RMR) $(OBJDIR)

fclean: clean
		$(RMR) $(BINDIR)
		cd $(LIBDIR) && make fclean

re: fclean all

.PHONY: all clean fclean re