/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ber.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:10 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:11 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	read_ber(t_mlx *mlx, t_map *map, char *ber)
{
	t_list	*lines;
	int		status;

	status = 0;
	lines = read_lines(ber);
	if (!lines)
		return (1);
	status = init_textures(mlx, &lines);
	if (!status)
		status = init_map(map, lines);
	if (!status)
		status = check_map(map);
	ft_lstclear(&lines, free);
	return (status);
}
