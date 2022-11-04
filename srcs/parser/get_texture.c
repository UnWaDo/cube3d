#include "cube_map.h"
#include "cube_utils.h"

static int	add_texture(t_mlx *mlx, char **params)
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

int	get_texture(t_mlx *mlx, char *line)
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
