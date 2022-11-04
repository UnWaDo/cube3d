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

#ifndef CUBE_UTILS_H
# define CUBE_UTILS_H

# include <math.h>

enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	ON_RESIZE = 25
};

enum
{
	KEYCODE_ENTER = 65293,
	KEYCODE_ESCAPE = 65307,
	KEYCODE_LEFT = 65361,
	KEYCODE_UP = 65362,
	KEYCODE_RIGHT = 65363,
	KEYCODE_DOWN = 65364,
	KEYCODE_W = 119,
	KEYCODE_A = 97,
	KEYCODE_S = 115,
	KEYCODE_D = 100,
	KEYCODE_SPACE = 32
};

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

double	vec_length(t_vec2 vec);
t_vec2	perpendicular(t_vec2 vec);
t_vec2	add_vec(t_vec2 v1, t_vec2 v2);
t_vec2	multipl_vec(t_vec2 v, double k);
t_vec2	rotate_vec(t_vec2 vec, double angle);
void	print_error(char *error);
void	print_error_with_add(char *error, char *additional);
void	print_error_with_number(char *error, int nbr);
int		make_dda(char **map, t_vec2 pos, t_vec2 ray, t_vec2 *l_h);

#endif