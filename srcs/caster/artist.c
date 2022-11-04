#include "cube.h"

static void	strip_img(t_img *src, t_img *dst, t_vec2 sx_h, t_pos w_h_dst)
{
	double	scaler;
	int		pixel;
	t_pos	src_pos;
	double	count;

	src_pos.x = sx_h.x * src->w_h.x;
	src_pos.y = 0;
	count = w_h_dst.y;
	scaler = sx_h.y / src->w_h.y;
	while (src_pos.y < src->w_h.y)
	{
		pixel = get_pixel(src, src_pos);
		put_rect(dst, w_h_dst, (t_pos){.x = 1,
			.y = (int)count - w_h_dst.y}, pixel);
		src_pos.y++;
		w_h_dst.y += (int)count - w_h_dst.y;
		count += scaler;
	}
}

static t_vec2	get_ray(int x, t_vec2 camera)
{
	t_vec2	ray;
	t_vec2	norm;

	norm = perpendicular(camera);
	ray = add_vec(camera, multipl_vec(norm, -1.0 + 2.0 * x / WIDTH));
	return (ray);
}

static void	draw_strip(t_img *img, t_map *map, int x, t_vec2 l_h)
{
	t_pos	corner;
	t_pos	w_h;

	corner = (t_pos){.x = x, .y = 0};
	w_h = (t_pos){.x = 1, .y = (0.5 - 0.25 / l_h.x) * HEIGHT};
	put_rect(map->canvas, corner, w_h, to_trgb(0, 166, 206, 227));
	corner.y += w_h.y;
	w_h.y = (0.5 / l_h.x) * HEIGHT;
	strip_img(img, map->canvas, (t_vec2){.x = l_h.y - (int)l_h.y,
		.y = w_h.y}, corner);
	corner.y += w_h.y;
	w_h.y = (0.5 - 0.25 / l_h.x) * HEIGHT;
	put_rect(map->canvas, corner, w_h, to_trgb(0, 178, 223, 138));
}

void	draw_screen(t_hero *hero, t_map *map, t_mlx *mlx)
{
	t_vec2	ray;
	t_pos	x_s;
	t_vec2	l_h;
	t_img	*img;

	x_s.x = 0;
	while (x_s.x < WIDTH)
	{
		ray = get_ray(x_s.x, hero->camera);
		x_s.y = make_dda(map->map, hero->pos, ray, &l_h);
		img = get_loaded_img(mlx->images, x_s.y);
		draw_strip(img, map, x_s.x, l_h);
		x_s.x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, map->canvas->img, 0, 0);
}
