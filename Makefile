# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 18:20:16 by ldedier           #+#    #+#              #
#    Updated: 2018/06/08 23:52:14 by lcavalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= rt

CC		= gcc

PWD = \"$(shell pwd)\"

OK_COLOR = \x1b[32;01m
EOC = \033[0m

DEBUG ?= 0

ifeq ($(DEBUG), 1)
	CFLAGS += -g -DDEBUG -fsanitize=address
else
	CFLAGS += -Ofast
endif

SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = includes

LIBFTDIR = libft
LIBFT_INCLUDEDIR = includes
LIBFT = $(LIBFTDIR)/libft.a

LIBMATDIR = libmat
LIBMAT_INCLUDEDIR = includes
LIBMAT = $(LIBMATDIR)/libmat.a

LIBSDL2DIR = ~/.brew/lib
LIBSDL2_INCLUDEDIR = ~/.brew/Cellar/sdl2/2.0.8/include/SDL2/
LIBSDL2TTF_INCLUDEDIR = ~/.brew/Cellar/sdl2_ttf/2.0.14/include/SDL2/

SRCS_NO_PREFIX = camera_rotations.c\
				 colors.c\
				 debug.c\
				 intersections.c\
				 lights.c\
				 normals.c\
				 normals2.c\
				 normals3.c\
				 obj_list.c\
				 paint_threaded.c\
				 parse_settings.c\
				 parse_main.c\
				 parse_obj.c\
				 parse_orsc.c\
				 parse_perts.c\
				 parse_others.c\
				 parse_specifics.c\
				 parse_specifics2.c\
				 parse_specifics_cobject.c\
				 parse_start.c\
				 parse_tools.c\
				 parse_read_tools.c\
				 parse_process.c\
				 parse_stack.c\
				 populate_world.c\
				 renderer.c\
				 viewplane.c\
				 rotations.c\
				 rt.c\
				 shadows.c\
				 tracer.c\
				 translations.c\
				 vectors.c\
				 vectors2.c\
				 world_maker.c\
				 loop.c\
				 key_events.c\
				 process.c \
				 world_init.c\
				 compute_matrix.c \
				 paint_fast.c \
				 paint_canvas.c\
				 compute_matrix.c\
				 ft_export_ppm.c\
				 ft_export_bmp.c\
				 ft_new_image.c\
				 ft_get_name.c\
				 ft_export.c\
				 ft_export_y4m.c\
				 lights_toon.c \
				 convolute.c\
				 filters.c\
				 intcolors.c\
				 perturbations.c\
				 errors.c\
				 refraction.c\
				 quartics_intersect.c\
				 quartics_intersect2.c\
				 cuts.c\
				 inequality.c\
				 parse_cut.c\
				 triangle.c\
				 parse_triangle.c\
				 ft_process_parse_obj.c\
				 ft_parse_obj_faces.c\
				 ft_parse_obj_vertices.c\
				 map_file.c\
				 tracer2.c\
				 insides.c\
				 automatic.c\
				 defining.c\
				 insides2.c\
				 video.c\
				 tools.c\
				 ft_parse_bmp.c\
				 parse_texture.c\
				 textures.c\
				 parse_plane_textures.c\
				 ft_parse_bmp.c\
				 ft_export_scene.c\
				 mouse_events.c\
				 menu.c\
				 perlin.c

INCLUDES_NO_PREFIX = rt.h objects.h export.h

SOURCES  = $(addprefix $(SRCDIR)/,      $(SRCS_NO_PREFIX))
OBJECTS  = $(addprefix $(OBJDIR)/,      $(SRCS_NO_PREFIX:%.c=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR) -I $(LIBFTDIR)/$(LIBFT_INCLUDEDIR)\
	  -I $(LIBMATDIR)/$(LIBMAT_INCLUDEDIR)\
	  -I $(LIBSDL2_INCLUDEDIR)\
	  -I $(LIBSDL2TTF_INCLUDEDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC)

LFLAGS = -L $(LIBFTDIR) -lft -L $(LIBMATDIR) -lmat

opti:
	@make -j all

all:
	@make -C $(LIBFTDIR) all
	@make -C $(LIBMATDIR) all
	@make $(BINDIR)/$(NAME)

debug:
	@make -j all DEBUG=1

$(BINDIR)/$(NAME): $(OBJECTS) $(LIBFT) $(LIBMAT)
	$(CC) -o $@ $^ $(LFLAGS) -L $(LIBSDL2DIR) -lsdl2 -lsdl2_ttf
	@echo "$(OK_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@make clean -C $(LIBFTDIR)
	@make clean -C $(LIBMATDIR)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)
	@make fclean -C $(LIBMATDIR)

re: fclean opti

.PHONY: all clean fclean re
