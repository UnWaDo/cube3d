/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:21 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:21 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_utils.h"

double	vec_length(t_vec2 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

t_vec2	perpendicular(t_vec2 vec)
{
	t_vec2	perp;

	perp = (t_vec2){.x = -vec.y / vec_length(vec),
		.y = vec.x / vec_length(vec)};
	return (perp);
}

t_vec2	add_vec(t_vec2 v1, t_vec2 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return (v1);
}

t_vec2	multipl_vec(t_vec2 v, double k)
{
	v.x *= k;
	v.y *= k;
	return (v);
}

t_vec2	rotate_vec(t_vec2 vec, double angle)
{
	return ((t_vec2){.x = vec.x * cos(angle) - vec.y * sin(angle),
		.y = vec.x * sin(angle) + vec.y * cos(angle)});
}
