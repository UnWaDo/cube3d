/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalex <lalex@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:47:00 by lalex             #+#    #+#             */
/*   Updated: 2022/11/04 16:47:01 by lalex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_error(char *error)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error, 2);
}

void	print_error_with_add(char *error, char *additional)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(additional, 2);
}

void	print_error_with_number(char *error, int nbr)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": ", 2);
	ft_putnbr_fd(nbr, 2);
	ft_putchar_fd('\n', 2);
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
