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
