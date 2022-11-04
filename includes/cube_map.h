#ifndef CUBE_MAP_H
# define CUBE_MAP_H

# include "cube_mlx.h"

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	t_img	*canvas;
}	t_map;

t_list	*read_lines(char *file);
int		read_ber(t_mlx *mlx, t_map *map, char *ber);
int		init_textures(t_mlx *mlx, t_list **lines);
int		get_texture(t_mlx *mlx, char *line);
int		add_color(t_mlx *mlx, char **params);
int		init_map(t_map *map, t_list *map_lines);
int		check_map(t_map *map);
void	draw_map(t_mlx *mlx, t_map *map);
void	delete_map(t_map *map);
void	print_map(t_map *map);

# define CELL_WIDTH		64

# define ALLOWED_CHARS	"01NWSE"
# define INVALID_NEIGHB	"0NWSE"
# define WHITESPACES	" "
# define MAP_FILE_ERR	"Invalid map file"
# define MAP_ALLOC_ERR	"Map allocation failed"
# define MAP_READ_ERR	"Map reading error"
# define MAP_SHAPE_ERR	"Map has an invalid format"
# define MAP_WALL_ERR	"Map is not surrounded by walls"
# define MAP_INV_ERR	"Invalid map char"
# define MAP_LINE_ERR	"Invalid map line"
# define MAP_HERO_ERR	"Zero or several hero positions"
# define MAP_EXIT_ERR	"Zero or several exit positions"
# define MAP_COLL_ERR	"Map must have at least 1 collectible"

# define OUB_CODE		' '
# define EMPTY_CODE		'0'
# define WALL_CODE		'1'
# define HERO_CODES		"NWSE"
# define HERO_NORTH		'N'
# define HERO_WEST		'W'
# define HERO_SOUTH		'S'
# define HERO_EAST		'E'

# define NO_DEF			"./imgs/bluestone.xpm"
# define SO_DEF			"./imgs/greystone.xpm"
# define EA_DEF			"./imgs/wood.xpm"
# define WE_DEF			"./imgs/wall21.xpm"

# define BG_COLOR		0101202202

#endif