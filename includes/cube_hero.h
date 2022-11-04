/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_hero.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:57 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:58 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_HERO_H
# define CUBE_HERO_H

# include "cube_map.h"
# include "cube_mlx.h"
# include "cube_utils.h"

typedef struct s_hero
{
	t_vec2	pos;
	t_vec2	camera;
}	t_hero;

int		init_hero(t_hero *hero, t_map *map);
void	move_hero(t_hero *hero, t_map *map, t_vec2 pos);
void	move_hero_rel(t_hero *hero, t_map *map, t_vec2 pos);
int		damage_hero(t_hero *hero, int damage);
void	print_hero_status(t_hero *hero);
void	game_over(t_hero *hero);

# define HERO_STEP		0.2
# define HERO_ROT		0.0873

# define STATUS_HEALTHY	0b1
# define STATUS_HURT	0b10
# define STATUS_DAMAGED	0b100
# define STATUS_DEAD	0b1000
# define STATUS_WON		0b10000

#endif