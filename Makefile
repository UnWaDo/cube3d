SOURCES_MAIN	=	main.c clean_cube.c utils.c init_cube.c
SOURCES_BERS	=	read_ber.c init_map.c read_lines.c check_map.c print_map.c
SOURCES_HERO	=	hero.c init_hero.c
SOURCES_MLX		=	mlx_init.c mlx_images.c mlx_utils.c 
SOURCES_CASTER	=	artist.c vec_utils.c dda.c
SOURCES_PARSER	=	textures.c get_texture.c colors.c
SOURCES_FN		=	$(addprefix main/,$(SOURCES_MAIN)) \
						$(addprefix bers/,$(SOURCES_BERS)) \
						$(addprefix mlx/,$(SOURCES_MLX)) \
						$(addprefix hero/,$(SOURCES_HERO)) \
						$(addprefix parser/,$(SOURCES_PARSER)) \
						$(addprefix caster/,$(SOURCES_CASTER))
SOURCES			=	$(addprefix srcs/,$(SOURCES_FN))
LIBFT_PATH		=	./libft/
LIBFT			=	$(LIBFT_PATH)/libft.a
MLX_PATH		=	./mlx/
MLX				=	$(MLX_PATH)/libmlx.a
INCLUDES		=	./includes/
HEADERS_LIBFT	=	$(addprefix $(LIBFT_PATH),libft.h)
HEADERS_CUBE	=	cube.h cube_map.h cube_mlx.h cube_hero.h \
					cube_utils.h
HEADERS			=	$(addprefix $(INCLUDES),$(HEADERS_CUBE)) \
					$(HEADERS_LIBFT)
NAME			=	cube
OBJECTS			=	$(SOURCES:.c=.o)
IFLAGS			=	$(addprefix -I,$(LIBFT_PATH) $(MLX_PATH) $(INCLUDES))
CFLAGS			=	-g -Wall -Wextra -Werror #-fsanitize=address
LFLAGS			=	-Lmlx -lmlx -framework OpenGL -framework AppKit -lm
.PHONY:			all clean fclean re norm

$(NAME):	$(OBJECTS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX) $(LFLAGS) -o $(NAME) $(IFLAGS)

all:		$(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX):
	make -C $(MLX_PATH)

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