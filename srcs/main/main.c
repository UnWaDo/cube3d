#include "cube.h"

int	close_ok(t_cube *cube)
{
	clean_cube(cube);
	exit(EXIT_SUCCESS);
}

int	key_movements(int keycode, t_cube *cube)
{
	if (keycode == KEYCODE_W)
		move_hero_rel(cube->hero, cube->map, (t_vec2){.x = HERO_STEP, .y = 0});
	else if (keycode == KEYCODE_S)
		move_hero_rel(cube->hero, cube->map, (t_vec2){.x = -HERO_STEP, .y = 0});
	else if (keycode == KEYCODE_A)
		move_hero_rel(cube->hero, cube->map, (t_vec2){.x = 0, .y = -HERO_STEP});
	else if (keycode == KEYCODE_D)
		move_hero_rel(cube->hero, cube->map, (t_vec2){.x = 0, .y = HERO_STEP});
	else if (keycode == KEYCODE_LEFT)
		cube->hero->camera = rotate_vec(cube->hero->camera, -HERO_ROT);
	else if (keycode == KEYCODE_RIGHT)
		cube->hero->camera = rotate_vec(cube->hero->camera, HERO_ROT);
	else
		return (0);
	draw_screen(cube->hero, cube->map, cube->mlx);
	return (0);
}

int	key_control(int keycode, t_cube *cube)
{
	if (keycode == KEYCODE_ESCAPE)
		close_ok(cube);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube	*cube;

	if (argc != 2)
	{
		print_error_with_number(ARGS_ERR, argc - 1);
		exit(EXIT_FAILURE);
	}
	cube = init_cube(argv[1]);
	if (cube == NULL)
		exit(EXIT_FAILURE);
	draw_screen(cube->hero, cube->map, cube->mlx);
	mlx_key_hook(cube->mlx->win_ptr, &key_control, cube);
	mlx_hook(cube->mlx->win_ptr, ON_KEYDOWN, (1L << 0), &key_movements, cube);
	mlx_hook(cube->mlx->win_ptr, ON_DESTROY, 0, &close_ok, cube);
	mlx_loop(cube->mlx->mlx_ptr);
	clean_cube(cube);
	return (0);
}
