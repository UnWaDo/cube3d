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

#ifndef CUBE_H
# define CUBE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# include "libft.h"
# include "cube_map.h"
# include "cube_mlx.h"
# include "cube_hero.h"

typedef struct s_cube
{
	t_hero	*hero;
	t_map	*map;
	t_mlx	*mlx;
}	t_cube;

t_cube		*init_cube(char *map);
int			close_ok(t_cube *so_long);
int			close_error(t_cube *so_long);
void		clean_cube(t_cube *cube);
void		free_lines(char **lines);
void		draw_screen(t_hero *hero, t_map *map, t_mlx *mlx);

# define CUBE_ALLOC_ERR	"Cube allocation failed"
# define ARGS_ERR		"Invalid number of arguments given (expected 1)"

# define WIDTH	1280
# define HEIGHT	840
# define TITLE	"Cube 3D..."

#endif