# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 22:20:49 by lcavalle          #+#    #+#              #
#    Updated: 2018/04/13 01:34:26 by lcavalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror 
SOURCES =	ft_atoi.c \
			ft_lstdelone.c \
			ft_memset.c \
			ft_putstr_fd.c \
			ft_strjoin.c \
			ft_strrchr.c \
		  	ft_bzero.c \
		  	ft_lstiter.c \
		  	ft_ndigits.c \
		  	ft_strcat.c \
		  	ft_strlcat.c \
		  	ft_strsplit.c \
		  	ft_isalnum.c \
		  	ft_lstmap.c \
		  	ft_nwords.c \
		  	ft_strchr.c \
		  	ft_strlen.c \
		  	ft_strstr.c \
		  	ft_isalpha.c \
		  	ft_lstnew.c \
		  	ft_pstrchr.c \
		  	ft_strclr.c \
		  	ft_strmap.c \
		  	ft_strsub.c \
		  	ft_isascii.c \
		  	ft_memalloc.c \
		  	ft_putchar.c \
		  	ft_strcmp.c \
		  	ft_strmapi.c \
		  	ft_strtrim.c \
		  	ft_isdigit.c \
		  	ft_memccpy.c \
		  	ft_putchar_fd.c \
		  	ft_strcpy.c \
		  	ft_strncat.c \
		  	ft_tolower.c \
		  	ft_isprint.c \
		  	ft_memchr.c \
		  	ft_putendl.c \
		  	ft_strdel.c \
		  	ft_strncmp.c \
		  	ft_toupper.c \
		  	ft_isspace.c \
		  	ft_memcmp.c \
		  	ft_putendl_fd.c \
		  	ft_strdup.c \
		  	ft_strncpy.c \
		  	ft_itoa.c \
		  	ft_memcpy.c \
		  	ft_putnbr.c \
		  	ft_strequ.c \
			ft_strnequ.c\
			ft_lstadd.c \
			ft_memdel.c \
			ft_putnbr_fd.c \
		  	ft_striter.c \
		  	ft_strnew.c \
		  	ft_lstdel.c \
		  	ft_memmove.c \
		  	ft_putstr.c \
		  	ft_striteri.c \
		  	ft_strnstr.c \
		  	ft_putctab.c \
			ft_strchri.c \
			ft_strndup.c \
			ft_strnjoin.c \
			ft_patoi.c \
			get_next_line.c \
			ft_freetab.c \
			ft_strskip.c \
			ft_putitab.c \
			ft_onesign.c \
			ft_patoi_hex.c \
			ft_patof.c

OBJ = $(SOURCES:.c=.o)
INCLUDES = -I includes

all: $(NAME)

$(NAME): $(OBJ)
	@echo "creating archive $(NAME)"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(NAME) created"

$(OBJ): %.o: %.c
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "removing $(NAME) object files"
	@rm -f $(OBJ)
	@echo "$(NAME) object files removed"

fclean: clean
	@echo "cleaning $(NAME)"
	@rm -f $(NAME)

re: fclean all

rec: re
	@/bin/rm -f $(OBJ)
	@echo "compling and cleaning files"
