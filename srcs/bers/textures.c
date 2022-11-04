#include "cube.h"

int	add_texture(t_mlx *mlx, char **params)
{
	int			i;
	int			len;
	const char	*names[] = {"NO", "SO", "WE", "EA"};
	const int	types[] = {I_NWALL_CODE, I_SWALL_CODE,
		I_WWALL_CODE, I_EWALL_CODE};

	len = ft_strlen(params[0]) + 1;
	i = (int)(sizeof(names) / sizeof(*names)) - 1;
	while (i >= 0 && ft_strncmp(params[0], names[i], len))
		i--;
	if (i < 0)
		print_error_with_add(BER_ID_ERR, params[0]);
	else if (get_loaded_img(mlx->images, types[i]))
		print_error_with_add(BER_ID_DUP_ERR, params[0]);
	else if (load_xpm_image(mlx, params[1], types[i]))
		return (0);
	return (1);
}

int	is_value(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line))
			return (0);
		line++;
	}
	return (1);
}

int	get_color_value(char *name, char **numbers, int nums[3])
{
	int		i;

	i = 0;
	while (numbers[i])
	{
		if (i > 2)
		{
			print_error_with_add(BER_TOO_MANY_C, name);
			return (1);
		}
		if (!is_value(numbers[i]))
		{
			print_error_with_add(BER_C_INVALID, numbers[i]);
			return (1);
		}
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

int	add_color(t_mlx *mlx, char **params)
{
	int		*color;
	int		nums[3];
	char	**numbers;
	int		status;

	if (!ft_strncmp(params[0], "F", 2))
		color = &(mlx->floor_c);
	else if (!ft_strncmp(params[0], "C", 2))
		color = &(mlx->ceiling_c);
	else
	{
		print_error_with_add(BER_ID_ERR, params[0]);
		return (1);
	}
	if (*color != -1)
	{
		print_error_with_add(BER_ID_DUP_ERR, params[0]);
		return (1);
	}
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

static t_f_txtr	get_function(char *name)
{
	const char	*textures[] = {"NO", "SO", "WE", "EA"};
	const char	*colors[] = {"C", "F"};
	int			i;
	int			len;

	len = ft_strlen(name) + 1;
	i = (int)(sizeof(textures) / sizeof(*textures)) - 1;
	while (i >= 0)
	{
		if (!ft_strncmp(name, textures[i], len))
			return (&add_texture);
		i--;
	}
	i = (int)(sizeof(colors) / sizeof(*colors));
	while (i >= 0)
	{
		if (!ft_strncmp(name, colors[i], len))
			return (&add_color);
		i--;
	}
	return (NULL);
}

static int	get_texture(t_mlx *mlx, char *line)
{
	char		**content;
	t_f_txtr	type;
	int			status;

	content = ft_split(line, ' ');
	if (!content)
	{
		print_error(MAP_ALLOC_ERR);
		return (1);
	}
	if (!content[1] || content[2])
	{
		free_lines(content);
		print_error_with_add(BER_IMG_ERR, line);
		return (1);
	}
	status = 1;
	type = get_function(content[0]);
	if (!type)
		print_error_with_add(BER_ID_ERR, content[0]);
	else
		status = (*type)(mlx, content);
	free_lines(content);
	return (status);
}

int	is_texture(char *line)
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

void	clear_until(t_list **lines, t_list *till)
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

int	check_textures(t_mlx *mlx)
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
