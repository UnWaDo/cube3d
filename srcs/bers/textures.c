#include "cube.h"

static void	free_lines(char **lines)
{
	int i;
	
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

static int	get_type(char *name)
{
	long		i;
	int			len;
	const char	*names[] = {"NO", "SO", "WE", "EA"};
	const int	types[] = {I_NWALL_CODE, I_SWALL_CODE, I_WWALL_CODE, I_EWALL_CODE};

	i = (int) (sizeof(names) / sizeof(*names)) - 1;
	len = ft_strlen(name) + 1;
	while (i >= 0
		&& ft_strncmp(name, names[i], len))
		i--;
	if (i < 0)
		return (-1);
	return (types[i]);
}

static int	get_texture(t_mlx *mlx, t_list **lines)
{
	char		**content;
	int			type;
	t_img		*img;
	t_list		*lst;

	if (*lines == NULL)
		return (-1);
	content = ft_split((*lines)->content, ' ');
	if (!content)
	{
		print_error(MAP_ALLOC_ERR);
		return (1);
	}
	type = get_type(content[0]);
	if (type < 0)
	{
		free_lines(content);
		return (-1);
	}
	img = NULL;
	if (content[1] && !content[2])
		img = load_xpm_image(mlx, content[1], type);
	else
		print_error_with_add(BER_IMG_ERR, (*lines)->content);
	lst = *lines;
	if (lst->next)
		*lines = lst->next;
	ft_lstdelone(lst, &free);
	free_lines(content);
	if (!img)
		return (1);
	return (0);
}

static int	get_default_textures(t_mlx *mlx)
{
	int			i;
	const int	types[] = {I_NWALL_CODE, I_SWALL_CODE, I_WWALL_CODE, I_EWALL_CODE};
	const char	*defaults[] = {NO_DEF, SO_DEF, WE_DEF, EA_DEF};

	i = (int) (sizeof(types) / sizeof(*types)) - 1;
	while (i >= 0)
	{
		if (get_loaded_img(mlx->images, types[i]) == NULL
			&& !load_xpm_image(mlx, defaults[i], types[i]))
			return (1);
		i--;
	}
	return (0);
}

int	init_textures(t_mlx *mlx, t_list **lines)
{
	int		status;

	status = get_texture(mlx, lines);
	while (!status)
		status = get_texture(mlx, lines);
	if (status > 0)
		return (1);
	return (get_default_textures(mlx));
}