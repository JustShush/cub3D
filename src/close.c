/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:48:46 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/31 10:48:57 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_game(t_general *gen)
{
	// mlx_clear_window(general->mlx, general->win);
	mlx_destroy_window(gen->mlx, gen->win);
	mlx_destroy_display(gen->mlx);
	free(gen->mlx);
	exit(0);
}