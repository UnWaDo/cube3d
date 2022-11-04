/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:30 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:36 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_mlx.h"

static t_img	*process_image(t_mlx *mlx, t_img *img)
{
	t_list	*new;

	if (img->img == NULL)
	{
		free(img);
		return (NULL);
	}
	new = ft_lstnew(img);
	if (!new)
	{
		mlx_destroy_image(mlx->mlx_ptr, img->img);
		free(img);
		return (NULL);
	}
	ft_lstadd_back(&(mlx->images), new);
	img->addr = mlx_get_data_addr(img->img,
			&(img->bpp), &(img->line_len), &(img->endian));
	return (img);
}

t_img	*create_new_image(t_mlx *mlx, t_pos w_h, int code)
{
	t_img	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->w_h = w_h;
	img->code = code;
	img->img = mlx_new_image(mlx->mlx_ptr, w_h.x, w_h.y);
	return (process_image(mlx, img));
}

t_img	*load_xpm_image(t_mlx *mlx, const char *path, int code)
{
	t_img	*img;

	img = malloc(sizeof(*img));
	if (!img)
		return (NULL);
	img->code = code;
	img->img = mlx_xpm_file_to_image(mlx->mlx_ptr,
			(char *)path, &(img->w_h.x), &(img->w_h.y));
	if (!img->img)
		print_error_with_add(MLX_IMG_OPEN_ERR, (char *) path);
	return (process_image(mlx, img));
}

t_img	*get_loaded_img(t_list *lst, int code)
{
	while (lst)
	{
		if (((t_img *)lst->content)->code == code)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}
