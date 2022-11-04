/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:48 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:49 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	is_texture(char *line)
{
	const char	*starts[] = {"NO", "SO", "WE", "EA", "C", "F"};
	int			i;

	i = (int)(sizeof(starts) / sizeof(*starts)) - 1;
	while (*line && *line == ' ')
		line++;
	while (i >= 0)
	{
		if (!ft_strncmp(line, starts[i], ft_strlen(starts[i])))
			return (1);
		i--;
	}
	return (0);
}

static void	clear_until(t_list **lines, t_list *till)
{
	t_list	*last;

	if (!(*lines) || *lines == till)
		return ;
	last = *lines;
	while (last->next && last->next != till)
		last = last->next;
	last->next = NULL;
	ft_lstclear(lines, &free);
	*lines = till;
}

static int	check_textures(t_mlx *mlx)
{
	const int	types[] = {I_NWALL_CODE, I_SWALL_CODE,
		I_WWALL_CODE, I_EWALL_CODE};
	const char	*names[] = {"NO", "SO", "WE", "EA"};
	int			i;

	i = (int)(sizeof(types) / sizeof(*types)) - 1;
	while (i >= 0)
	{
		if (!get_loaded_img(mlx->images, types[i]))
		{
			print_error_with_add(BER_UNDEF_TEXT_ERR, (char *)names[i]);
			return (1);
		}
		i--;
	}
	if (mlx->ceiling_c < 0)
		print_error_with_add(BER_UNDEF_COL_ERR, "C");
	else if (mlx->floor_c < 0)
		print_error_with_add(BER_UNDEF_COL_ERR, "F");
	else
		return (0);
	return (1);
}

int	init_textures(t_mlx *mlx, t_list **lines)
{
	int		status;
	t_list	*cur;

	cur = *lines;
	status = 0;
	while (cur && !status)
	{
		if (!ft_strlen(cur->content))
		{
			cur = cur->next;
			continue ;
		}
		if (is_texture(cur->content))
			status = get_texture(mlx, cur->content);
		else
			break ;
		cur = cur->next;
	}
	clear_until(lines, cur);
	if (status > 0)
		return (1);
	return (check_textures(mlx));
}
