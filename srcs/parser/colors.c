/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:43 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:45 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_map.h"
#include "cube_utils.h"

static int	is_ok(char *name, char **numbers, int i)
{
	if (i > 2)
	{
		print_error_with_add(BER_TOO_MANY_C, name);
		return (0);
	}
	if (!is_value(numbers[i]))
	{
		print_error_with_add(BER_C_INVALID, numbers[i]);
		return (0);
	}
	return (1);
}

int	get_color_value(char *name, char **numbers, int nums[3])
{
	int		i;

	i = 0;
	while (numbers[i])
	{
		if (!is_ok(name, numbers, i))
			return (1);
		nums[i] = ft_atoi(numbers[i]);
		if (nums[i] < 0 || nums[i] > 255)
		{
			print_error_with_number(BER_C_OUT_OF_RANGE, nums[i]);
			return (1);
		}
		i++;
	}
	if (i < 3)
	{
		print_error_with_number(BER_NOT_ENOUGH_C, i);
		return (1);
	}
	return (0);
}

static int	*get_pointer(t_mlx *mlx, char *name)
{
	int	*ptr;

	if (!ft_strncmp(name, "F", 2))
		ptr = &(mlx->floor_c);
	else if (!ft_strncmp(name, "C", 2))
		ptr = &(mlx->ceiling_c);
	else
	{
		print_error_with_add(BER_ID_ERR, name);
		return (NULL);
	}
	if (*ptr != -1)
	{
		print_error_with_add(BER_ID_DUP_ERR, name);
		return (NULL);
	}
	return (ptr);
}

int	add_color(t_mlx *mlx, char **params)
{
	int		*color;
	int		nums[3];
	char	**numbers;
	int		status;

	color = get_pointer(mlx, params[0]);
	if (!color)
		return (1);
	numbers = ft_split(params[1], ',');
	if (!numbers)
	{
		print_error(MAP_ALLOC_ERR);
		return (1);
	}
	status = get_color_value(params[0], numbers, nums);
	free_lines(numbers);
	if (!status)
		*color = to_trgb(0, nums[0], nums[1], nums[2]);
	return (status);
}
