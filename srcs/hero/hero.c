#include "cube_hero.h"

void	move_hero(t_hero *hero, t_map *map, t_vec2 pos)
{
	if (map->map[(int) pos.y][(int) pos.x] == WALL_CODE)
		return ;
	hero->pos = pos;
}

void	move_hero_rel(t_hero *hero, t_map *map, t_vec2 pos)
{
	t_vec2	abs_pos;
	t_vec2	norm;

	norm = perpendicular(hero->camera);
	abs_pos = hero->pos;
	abs_pos.x += pos.x * hero->camera.x;
	abs_pos.y += pos.x * hero->camera.y;
	abs_pos.x += pos.y * norm.x;
	abs_pos.y += pos.y * norm.y;
	move_hero(hero, map, abs_pos);
}
