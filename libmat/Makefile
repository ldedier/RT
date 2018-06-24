# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldedier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/06/12 17:27:59 by ldedier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libmat.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -fsanitize=address
endif

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes

OK_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX = ft_vec.c ft_mat_mult.c ft_translate.c ft_scale.c\
				 ft_rotate.c ft_normalize.c ft_vec_op.c ft_mat_vec_mult.c\
				 ft_model_view_matrix.c


SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.c=%.o))

INC_PATH = -I $(INCLUDESDIR)
INCLUDES_NO_PREFIX = libmat.h
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

CFLAGS += $(INC_PATH)

all: $(BINDIR)/$(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BINDIR)/$(NAME): $(OBJECTS)
	@ar rc $@ $^
	@ranlib $(NAME)
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"
clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(BINDIR)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
