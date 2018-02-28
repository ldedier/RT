# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/07 00:32:26 by lcavalle          #+#    #+#              #
#    Updated: 2018/02/28 01:48:36 by lcavalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
FLAGS = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
HEADDIR = headers
SOURCES :=	$(SRCDIR)/colors.c \
			$(SRCDIR)/input.c \
			$(SRCDIR)/intersections.c \
			$(SRCDIR)/normals.c \
			$(SRCDIR)/obj_list.c \
			$(SRCDIR)/paint_threaded.c \
			$(SRCDIR)/populate_world.c \
			$(SRCDIR)/renderer.c \
			$(SRCDIR)/rt.c \
			$(SRCDIR)/tracer.c \
			$(SRCDIR)/transforms.c \
			$(SRCDIR)/vectors.c \
			$(SRCDIR)/world_maker.c
HEADS :=	$(HEADDIR)/rt.h
OBJ = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
INCLUDES = -I libft -I lmlx -I headers
LIBS = -L libft/ -lft -L minilibx_macos/ -lmlx -lpthread
FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): lib $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LIBS) $(FRAMEWORKS)
	@echo "Linking complete!! :D"
lib: 
	@echo "compiling libft"
	@make -C libft/
	@echo "libft compiled"
	@echo "compiling minilibx"
	@make -C minilibx_macos/
	@echo "minilibx compiled"

$(OBJ): $(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADS) 
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "removing $(NAME) objectct files"
	@rm -f $(OBJ)
	@echo "$(NAME) object files removed"
	@make -C libft/ clean
	@make -C minilibx_macos/ clean

fclean:	clean
	@echo "cleaning $(NAME)"
	@rm -f $(NAME)
	@make -C libft/ fclean
	@make -C minilibx_macos/ clean

re:	fclean all
