/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mira <mira@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:01 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/04 13:17:04 by mira             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_key(int key, t_general *gen)
{
	if (key == 65307)
		close_game(gen);
	return (0);
}

//A and W dont work correctly. Have to add or subtract based on the players direction.
int	input(int key, t_general *gen)
{
	esc_key(key, gen);
	if (key == 65363) //left arrow
		gen->player->an = norm(gen->player->an - 10);
	if (key == 65361) //right arrow
		gen->player->an = norm(gen->player->an + 10);
	/* if (key == 97)//A
	{
		gen->player->x -= cos((gen->player->an) * 10;
		gen->player->y -= sin((gen->player->an) * 10;
	}
	if (key == 100) //D
	{
		gen->player->x += cos(toRad(gen->player->an)) * 10;
		gen->player->y += sin(toRad(gen->player->an)) * 10;
	} */
	if (key == 119)//W
	{
		gen->player->x -= cos(toRad(gen->player->an)) * 10;
		gen->player->y -= sin(toRad(gen->player->an)) * 10;
	}
	if (key == 115)//S
	{
		gen->player->x += cos(toRad(gen->player->an)) * 10;
		gen->player->y += sin(toRad(gen->player->an)) * 10;
	}
	printf("Player Dir: %f\n", gen->player->an);
	printf("Player y: %d; ", gen->player->y);
	printf("Player X: %d\n; ", gen->player->x);
	/* printf("Key: %i\n", key); */
	return (0);
}
