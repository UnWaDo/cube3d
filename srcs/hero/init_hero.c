#include "cube_hero.h"

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
				hero->pos = (t_vec2) {.x = x + 0.5, .y = y + 0.5};
				if (map->map[y][x] == HERO_NORTH)
					hero->camera = (t_vec2) {.x = 0, .y = -1};
				else if (map->map[y][x] == HERO_SOUTH)
					hero->camera = (t_vec2) {.x = 0, .y = 1};
				else if (map->map[y][x] == HERO_WEST)
					hero->camera = (t_vec2) {.x = -1, .y = 0};
				else if (map->map[y][x] == HERO_EAST)
					hero->camera = (t_vec2) {.x = 1, .y = 0};
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
