#include "cube.h"
#include "libft.h"

static int	alloc_map(t_map *map)
{
	int	i;

	map->map = malloc(map->height * sizeof(*(map->map)));
	if (map->map == NULL)
		return (1);
	i = 0;
	while (i < map->height)
	{
		map->map[i] = malloc(map->width * sizeof(**(map->map)));
		if (map->map[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

static int	get_max_width(t_list *map_lines)
{
	size_t	width;
	size_t	max;

	max = ft_strlen(map_lines->content);
	while (map_lines)
	{
		width = ft_strlen(map_lines->content);
		if (width > max)
			max = width;
		map_lines = map_lines->next;
	}
	if (width > __INT_MAX__)
		return (0);
	return ((int) width);
}

static void	fill_map(t_map *map, t_list *map_lines)
{
	int		x;
	int		y;
	char	*line;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		line = map_lines->content;
		while (line[x])
		{
			map->map[y][x] = line[x];
			x++;
		}
		while (x < map->width)
			map->map[y][x++] = OUB_CODE;
		y++;
		map_lines = map_lines->next;
	}
}

int	init_map(t_map *map, t_list *map_lines)
{
	map->height = ft_lstsize(map_lines);
	map->width = get_max_width(map_lines);
	if (map->width <= 2 || map->height <= 2)
	{
		print_error(MAP_SHAPE_ERR);
		return (1);
	}
	if (alloc_map(map))
	{
		print_error(MAP_ALLOC_ERR);
		return (1);
	}
	fill_map(map, map_lines);
	return (0);
}
