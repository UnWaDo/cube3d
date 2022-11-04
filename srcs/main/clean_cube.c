#include "cube.h"

void	clean_hero(t_hero *hero)
{
	free(hero);
}

void	clean_map(t_map *map)
{
	int	i;

	if (map->map)
	{
		i = 0;
		while (i < map->height && map->map[i])
			free(map->map[i++]);
		free(map->map);
	}
	free(map);
}

void	clean_mlx(t_mlx *mlx)
{
	t_list	*el;
	t_list	*next;

	el = mlx->images;
	while (el)
	{
		next = el->next;
		mlx_destroy_image(mlx->mlx_ptr, ((t_img *)(el->content))->img);
		free(el->content);
		free(el);
		el = next;
	}
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
		mlx_destroy_display(mlx->mlx_ptr);
	free(mlx);
}

void	clean_cube(t_cube *cube)
{
	if (cube->hero)
		clean_hero(cube->hero);
	if (cube->map)
		clean_map(cube->map);
	if (cube->mlx)
		clean_mlx(cube->mlx);
	free(cube);
}

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}
