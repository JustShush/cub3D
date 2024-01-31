/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:01 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/01/31 17:39:07 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_key(int key, t_game *game)
{
	if (key == 65307)
		close_game(game);
	return (0);
}

//A and W dont work correctly. Have to add or subtract based on the players direction.
int	input(int key, t_game *game)
{
	esc_key(key, game);
	if (key == 65363) //left arrow
		game->player->dir = norm(game->player->dir - 10);
	if (key == 65361) //right arrow
		game->player->dir = norm(game->player->dir + 10);
	if (key == 97)//A
	{
		game->player->x -= cos((game->player->dir * M_PI/180) + (M_PI / 2)) * 10;
		game->player->y -= sin((game->player->dir * M_PI/180) + (M_PI / 2)) * 10;
	}
	if (key == 100) //D
	{
		game->player->x += cos((game->player->dir * M_PI/180) + (M_PI / 2)) * 10;
		game->player->y += sin((game->player->dir * M_PI/180) + (M_PI / 2)) * 10;
	}
	if (key == 119)//W
	{
		game->player->x -= cos((game->player->dir * M_PI/180)) * 10;
		game->player->y -= sin((game->player->dir * M_PI/180)) * 10;
	}
	if (key == 115)//S
	{
		game->player->x += cos((game->player->dir * M_PI/180)) * 10;
		game->player->y += sin((game->player->dir * M_PI/180)) * 10;
	}
	printf("Player Dir: %f\n", game->player->dir);
	printf("Player y: %d; ", game->player->y);
	printf("Player X: %d\n; ", game->player->x);
	/* printf("Key: %i\n", key); */
	return (0);
}
