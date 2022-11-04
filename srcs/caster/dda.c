/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:19 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:19 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_utils.h"
#include "cube_map.h"

static t_vec2	init_dda(t_vec2 ray, t_vec2 pos, t_pos *map, t_pos *steps)
{
	t_vec2	delta;

	delta.x = fabs(1 / ray.x);
	delta.y = fabs(1 / ray.y);
	map->x = (int) pos.x;
	map->y = (int) pos.y;
	steps->x = 1 - 2 * (ray.x < 0);
	steps->y = 1 - 2 * (ray.y < 0);
	return (delta);
}

static t_vec2	init_dists(t_pos map, t_vec2 ray, t_vec2 pos, t_vec2 delta)
{
	t_vec2	dists;

	if (ray.x > 0)
		dists.x = (map.x + 1 - pos.x);
	else
		dists.x = (pos.x - map.x);
	if (ray.y > 0)
		dists.y = (map.y + 1 - pos.y);
	else
		dists.y = (pos.y - map.y);
	dists.x *= delta.x;
	dists.y *= delta.y;
	return (dists);
}

static int	finish_dda(t_pos s_st, t_vec2 *l_h, t_vec2 pos, t_vec2 ray)
{
	const int	codes[] = {I_WWALL_CODE, I_EWALL_CODE,
		I_SWALL_CODE, I_NWALL_CODE};
	int			side;

	side = codes[(s_st.x << 1) + (s_st.y < 0)];
	if (s_st.x)
	{
		l_h->x = l_h->y;
		l_h->y = pos.x + l_h->x * ray.x;
		return (side);
	}
	else
	{
		l_h->x = l_h->x;
		l_h->y = pos.y + l_h->x * ray.y;
		return (side);
	}
}

int	make_dda(char **map, t_vec2 pos, t_vec2 ray, t_vec2 *l_h)
{
	t_vec2	delta;
	t_pos	steps;
	t_pos	map_pos;
	int		side;

	delta = init_dda(ray, pos, &map_pos, &steps);
	*l_h = init_dists(map_pos, ray, pos, delta);
	while (map[map_pos.y][map_pos.x] != WALL_CODE)
	{
		side = (l_h->x >= l_h->y);
		if (l_h->x < l_h->y)
		{
			l_h->x += delta.x;
			map_pos.x += steps.x;
		}
		else
		{
			l_h->y += delta.y;
			map_pos.y += steps.y;
		}
	}
	l_h->x -= delta.x;
	l_h->y -= delta.y;
	return (finish_dda((t_pos){.x = side, .y = steps.x * (side == 0)
			+ steps.y * (side != 0)}, l_h, pos, ray));
}
