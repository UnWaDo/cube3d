/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@students.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 23:24:44 by lalex             #+#    #+#             */
/*   Updated: 2022/01/03 18:34:24 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_MLX_H
# define CUBE_MLX_H

# include <stdlib.h>
# include <mlx.h>
# include "libft.h"
# include "cube_utils.h"
# include <string.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_list	*images;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		code;
	t_pos	w_h;
}	t_img;

enum	IMG_CODES
{
	I_MAP_CODE,
	I_NWALL_CODE,
	I_WWALL_CODE,
	I_SWALL_CODE,
	I_EWALL_CODE,
};

# define MLX_ALLOC_ERR		"MLX allocation failed"
# define MLX_INIT_ERR		"MLX didn't start"
# define MLX_WIN_ERR		"Window didn't open"
# define MLX_IMG_OPEN_ERR	"Invalid image"
# define MLX_IMG_ERR		"Image creation failed"
# define BER_IMG_ERR		"Invalid texture line"

# define HERO_IMG		"imgs/human.xpm"
# define EMPTY_IMG		"imgs/floor.xpm"
# define WALL_IMG		"imgs/wall.xpm"
# define COLL_IMG		"imgs/bag_coins.xpm"
# define ENEMY_IMG		"imgs/goblin.xpm"
# define EXIT_IMG		"imgs/flag_red.xpm"

int		init_mlx(t_mlx *mlx);
int		init_win(t_mlx *mlx);

int		to_trgb(unsigned char t,
			unsigned char r, unsigned char g, unsigned char b);
void	put_pixel(t_img *img, t_pos pos, int c);
int		get_pixel(t_img *img, t_pos pos);
void	put_rect(t_img *img, t_pos corner, t_pos w_h, int c);
void	fill_color(t_img *img, int c);
t_mlx	*start_mlx_win(t_pos w_h, char *title);
t_img	*create_new_image(t_mlx *mlx, t_pos w_h, int code);
t_img	*load_xpm_image(t_mlx *mlx, const char *path, int code);
t_img	*get_loaded_img(t_list *lst, int code);
void	strip_img(t_img *src, t_img *dst, double strp_x, t_pos w_h_dst, int height);
void	clear_mlx(t_mlx *mlx);

#endif