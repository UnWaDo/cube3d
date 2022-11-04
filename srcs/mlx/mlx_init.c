/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:32 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:35 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_mlx.h"
#include "cube.h"

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
	{
		print_error(MLX_ALLOC_ERR);
		return (1);
	}
	mlx->floor_c = -1;
	mlx->ceiling_c = -1;
	return (0);
}

int	init_win(t_mlx *mlx)
{
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, \
		WIDTH, HEIGHT, TITLE);
	if (mlx->win_ptr == NULL)
	{
		print_error(MLX_WIN_ERR);
		return (1);
	}
	return (0);
}
