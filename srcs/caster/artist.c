#include "cube.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define RAYS			100
#define WALL_HEIGHT		100
#define CAMERA_HEIGHT	10

double	vec_length(t_vec2 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

t_vec2	perpendicular(t_vec2 vec)
{
	t_vec2	perp;

	perp = (t_vec2) {.x = -vec.y/vec_length(vec), .y = vec.x / vec_length(vec)};
	return (perp);
}

t_vec2	add_vec(t_vec2 v1, t_vec2 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return (v1);
}

t_vec2	multipl_vec(t_vec2 v, double k)
{
	v.x *= k;
	v.y *= k;
	return (v);
}

t_vec2	get_ray(int x, t_vec2 camera)
{
	t_vec2	ray;
	t_vec2	norm;

	norm = perpendicular(camera);
	ray = add_vec(camera, multipl_vec(norm, -1.0 + 2.0 * x / WIDTH));
	return (ray);
}

double	make_dda(t_map *map, t_vec2 pos, t_vec2 ray, int *side, double *hit)
{
	t_vec2	delta;
	t_vec2	dists;
	t_pos	steps;
	t_pos	map_pos;

	delta.x = fabs(1 / ray.x);
	delta.y = fabs(1 / ray.y);
	map_pos.x = (int) pos.x;
	map_pos.y = (int) pos.y;
	steps.x = 1 - 2 * (ray.x < 0);
	steps.y = 1 - 2 * (ray.y < 0);
	if (ray.x > 0)
		dists.x = (map_pos.x + 1 - pos.x);
	else
		dists.x = (pos.x - map_pos.x);
	if (ray.y > 0)
		dists.y = (map_pos.y + 1 - pos.y);
	else
		dists.y = (pos.y - map_pos.y);
	dists.x *= delta.x;
	dists.y *= delta.y;
	while (map->map[map_pos.y][map_pos.x] != WALL_CODE)
	{
		if (dists.x < dists.y)
		{
			dists.x += delta.x;
			map_pos.x += steps.x;
			*side = 0;
		}
		else
		{
			dists.y += delta.y;
			map_pos.y += steps.y;
			*side = 1;
		}
	}
	if (*side)
	{
		if (ray.y > 0)
			*side = 2;
		else
			*side = 0;
	}
	else
	{
		if (ray.x > 0)
			*side = 3;
		else
			*side = 1;
	}
	if (*side % 2)
	{
		*hit = pos.y + (dists.x - delta.x) * ray.y;
		return (dists.x - delta.x);
	}
	*hit = pos.x + (dists.y - delta.y) * ray.x;
	return (dists.y - delta.y);
}

void draw_screen(t_hero *hero, t_map *map, t_mlx *mlx)
{
	t_vec2	ray;
	int		side;
	double	hit;
	t_img	*img;
	int		x;
	const int	sides[] = {I_NWALL_CODE, I_EWALL_CODE, I_SWALL_CODE, I_WWALL_CODE};

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray(x, hero->camera);
		double length = make_dda(map, hero->pos, ray, &side, &hit);
		img = get_loaded_img(mlx->images, sides[side]);
		t_pos corner = {.x = x, .y = 0};
		t_pos w_h = {.x = 1, .y = (0.5 - 0.25 / length) * HEIGHT};
		put_rect(map->canvas, corner, w_h, to_trgb(0, 166, 206, 227));
		corner.y = w_h.y;
		w_h.y = (0.5 / length) * HEIGHT;
		strip_img(img, map->canvas, hit - (int) hit, corner, w_h.y);
		corner.y += w_h.y;
		w_h.y = (0.5 - 0.25 / length) * HEIGHT;
		put_rect(map->canvas, corner, w_h, to_trgb(0, 178, 223, 138));
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, map->canvas->img, 0, 0);
}

t_vec2	rotate_vec(t_vec2 vec, double angle)
{
	return ((t_vec2) {.x = vec.x * cos(angle) - vec.y * sin(angle), 
		.y = vec.x * sin(angle) + vec.y * cos(angle)});
}
