/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:46:57 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:46:58 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	init_canvas(t_mlx *mlx, t_map *map)
{
	map->canvas = create_new_image(mlx,
			(t_pos){.x = WIDTH, .y = HEIGHT}, I_MAP_CODE);
	if (map->canvas == NULL)
	{
		print_error(MLX_IMG_ERR);
		return (1);
	}
	return (0);
}

t_cube	*init_cube(char *ber)
{
	t_cube	*cube;

	cube = ft_calloc(1, sizeof(*cube));
	if (!cube)
	{
		print_error(CUBE_ALLOC_ERR);
		return (NULL);
	}
	cube->mlx = ft_calloc(1, sizeof(*(cube->mlx)));
	cube->hero = ft_calloc(1, sizeof(*(cube->hero)));
	cube->map = ft_calloc(1, sizeof(*(cube->map)));
	if (!cube->mlx || !cube->hero || !cube->map)
	{
		print_error(CUBE_ALLOC_ERR);
		clean_cube(cube);
		return (NULL);
	}
	if (init_mlx(cube->mlx) || read_ber(cube->mlx, cube->map, ber)
		|| init_hero(cube->hero, cube->map) || init_win(cube->mlx)
		|| init_canvas(cube->mlx, cube->map))
	{
		clean_cube(cube);
		return (NULL);
	}
	return (cube);
}
