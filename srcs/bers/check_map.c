#include "cube_map.h"

static int	check_surround(t_map *map, int x, int y)
{
	if (map->map[y][x] == OUB_CODE || map->map[y][x] == WALL_CODE)
		return (0);
	if (x > 0)
	{
		if (y > 0 && map->map[y - 1][x - 1] == OUB_CODE)
			return (1);
		if (map->map[y][x - 1] == OUB_CODE)
			return (1);
		if (y < map->height - 1 && map->map[y + 1][x - 1] == OUB_CODE)
			return (1);
	}
	if (y > 0 && map->map[y - 1][x] == OUB_CODE)
		return (1);
	if (y < map->height - 1 && map->map[y + 1][x] == OUB_CODE)
		return (1);
	if (x < map->width - 1)
	{
		if (y > 0 && map->map[y - 1][x + 1] == OUB_CODE)
			return (1);
		if (map->map[y][x + 1] == OUB_CODE)
			return (1);
		if (y < map->height - 1 && map->map[y + 1][x + 1] == OUB_CODE)
			return (1);
	}
	return (0);
}

static int	check_line(t_map *map, int y, int *heroes)
{
	int	x;

	x = 0;
	while (x < map->width && map->map[y][x] == OUB_CODE)
		x++;
	if (x >= map->width || map->map[y][x++] != WALL_CODE)
		return (1);
	while (x < map->width && map->map[y][x] != OUB_CODE)
	{
		if ((y == 0 || y == map->height - 1) && map->map[y][x] != WALL_CODE)
			return (1);
		if (check_surround(map, x, y))
			return (1);
		if (!ft_strchr(ALLOWED_CHARS, map->map[y][x]))
			return (1);
		if (ft_strchr(HERO_CODES, map->map[y][x]))
			(*heroes)++;
		x++;
	}
	while (x < map->width)
		x++;
	return (0);
}

int	check_map(t_map *map)
{
	int		met_hero;
	int		i;

	i = 0;
	met_hero = 0;
	while (i < map->height && met_hero <= 1 && !check_line(map, i, &met_hero))
		i++;
	if (i < map->height)
		print_error_with_number(MAP_LINE_ERR, i + 1);
	else if (met_hero != 1)
		print_error(MAP_HERO_ERR);
	return (met_hero != 1 || i < map->height);
}
