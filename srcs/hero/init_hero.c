#include "cube_hero.h"

static t_vec2	get_camera_dir(char code)
{
	const char		codes[] = {HERO_NORTH, HERO_SOUTH, HERO_WEST, HERO_EAST};
	const t_vec2	cameras[] = {{.x = 0, .y = -1}, {.x = 0, .y = 1},
	{.x = -1, .y = 0}, {.x = 1, .y = 0}};
	unsigned long	i;

	i = 0;
	while (i < sizeof(codes) / sizeof(*codes) && codes[i] != code)
		i++;
	return (cameras[i]);
}

static void	get_hero_pos(t_hero *hero, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (ft_strchr(HERO_CODES, map->map[y][x]))
			{
				hero->pos = (t_vec2){.x = x + 0.5, .y = y + 0.5};
				hero->camera = get_camera_dir(map->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_hero(t_hero *hero, t_map *map)
{
	get_hero_pos(hero, map);
	return (0);
}
