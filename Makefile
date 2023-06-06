# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:46:57 by aselnet           #+#    #+#              #
#    Updated: 2023/06/05 16:51:05 by orazafy          ###   ########.fr        #
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
BUILTINSDIR = builtins

EXEC_FILES = ft_execute.c

PARSING_FILES = define.c \
		define2.c \
		expand.c \
		init.c \
		lexing.c \
		parsing.c \
		quit.c \
		temp.c \
		tokens.c \
		tokens2.c \
		utils.c

BUILTINS_FILES = ft_builtins_utils_2.c \
				ft_builtins_utils.c \
				ft_cd_utils.c \
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_environment_utils_2.c \
				ft_environment_utils.c \
				ft_export_utils.c \
				ft_export.c \
				ft_pwd.c \
				ft_unset.c

EXEC = $(addprefix $(EXECDIR)/, $(EXEC_FILES))
PARSING = $(addprefix $(PARSINGDIR)/, $(PARSING_FILES))
BUILTINS = $(addprefix $(BUILTINSDIR)/, $(BUILTINS_FILES))
SRCS = $(addprefix $(SRCDIR)/, minishell.c $(EXEC) $(PARSING) $(BUILTINS))
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