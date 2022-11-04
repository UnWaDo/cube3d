#include "cube_mlx.h"

int	to_trgb(unsigned char t,
		unsigned char r, unsigned char g, unsigned char b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_pixel(t_img *img, t_pos pos, int c)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x > img->w_h.x || pos.y > img->w_h.y)
		return ;
	dst = img->addr + (pos.y * img->line_len + pos.x * (img->bpp / 8));
	((unsigned int *)dst)[0] = c;
}

int	get_pixel(t_img *img, t_pos pos)
{
	char	*dst;

	if (pos.x < 0 || pos.y < 0 || pos.x > img->w_h.x || pos.y > img->w_h.y)
		return (0);
	dst = img->addr + (pos.y * img->line_len + pos.x * (img->bpp / 8));
	return (((unsigned int *)dst)[0]);
}

void	put_rect(t_img *img, t_pos corner, t_pos w_h, int c)
{
	t_pos	till;

	till = (t_pos){.x = corner.x + w_h.x, .y = corner.y + w_h.y};
	while (corner.y < till.y)
	{
		while (corner.x < till.x)
		{
			put_pixel(img, corner, c);
			corner.x++;
		}
		corner.x -= w_h.x;
		corner.y++;
	}
}

void	fill_color(t_img *img, int c)
{
	put_rect(img, (t_pos){.x = 0, .y = 0}, img->w_h, c);
}

void	strip_img(t_img *src, t_img *dst, double strp_x, t_pos w_h_dst, int height)
{
	double	scaler;
	int		pixel;
	t_pos	src_pos;
	double	count;

	src_pos.x = strp_x * src->w_h.x;
	src_pos.y = 0;
	count = w_h_dst.y;
	scaler = 1.0 * height / src->w_h.y;
	while (src_pos.y < src->w_h.y)
	{
		pixel = get_pixel(src, src_pos);
		put_rect(dst, w_h_dst, (t_pos) {.x = 1, .y = (int) count - w_h_dst.y}, pixel);
		src_pos.y++;
		w_h_dst.y += (int) count - w_h_dst.y;
		count += scaler;
	}
}