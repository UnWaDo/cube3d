SOURCES_MAIN	=	main.c clean_cube.c utils.c
SOURCES_BERS	=	read_ber.c init_map.c read_lines.c textures.c check_map.c print_map.c
SOURCES_HERO	=	hero.c init_hero.c
SOURCES_MLX		=	mlx_init.c mlx_images.c mlx_utils.c 
SOURCES_CASTER	=	artist.c
SOURCES_FN		=	$(addprefix main/,$(SOURCES_MAIN)) \
						$(addprefix bers/,$(SOURCES_BERS)) \
						$(addprefix mlx/,$(SOURCES_MLX)) \
						$(addprefix hero/,$(SOURCES_HERO)) \
						$(addprefix caster/,$(SOURCES_CASTER))
SOURCES			=	$(addprefix srcs/,$(SOURCES_FN))
LIBFT_PATH		=	./libft/
LIBFT			=	$(LIBFT_PATH)/libft.a
INCLUDES		=	./includes/
HEADERS_LIBFT	=	$(addprefix $(LIBFT_PATH),libft.h)
HEADERS_CUBE	=	cube.h cube_map.h cube_mlx.h cube_hero.h \
					cube_mlx.h cube_utils.h
HEADERS			=	$(addprefix $(INCLUDES),$(HEADERS_CUBE)) \
					$(HEADERS_LIB)
NAME			=	cube
OBJECTS			=	$(SOURCES:.c=.o)
IFLAGS			=	$(addprefix -I,$(LIBFT_PATH) $(INCLUDES))
CFLAGS			=	-g -Wall -Wextra -Werror #-fsanitize=address
LFLAGS			=	-lmlx -lX11 -lXext -lm
.PHONY:			all clean fclean re norm

$(NAME):	$(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(LFLAGS) -o $(NAME) $(IFLAGS)

all:		$(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

%.o:		%.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $< $(IFLAGS)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)

fclean:		clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re:			fclean all

norm:
	norminette $(SOURCES) $(HEADERS)