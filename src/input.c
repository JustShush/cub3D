/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:01 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/06 15:24:09 by ddiniz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	esc_key(int key, t_general *gen)
{
	if (key == 65307)
		close_game(gen);
	return (0);
}

int	key_press(int key, t_general *gen)
{
	esc_key(key, gen);
	if (key == 65363) //left arrow
		gen->key->l = 1;
	if (key == 65361) //right arrow
		gen->key->r = 1;
	if (key == 97)//A
		gen->key->a = 1;
	if (key == 100)//D
		gen->key->d = 1;
	if (key == 119)//W
		gen->key->w = 1;
	if (key == 115)//S
		gen->key->s = 1;
	printf("Player y: %f\n", gen->player->y);
	printf("Player X: %f\n;", gen->player->x);
	printf("Player Dir: %f\n", gen->player->an);
	return (0);
}

int	key_release(int key, t_general *gen)
{
	if (key == 65363) //left arrow
		gen->key->l = 0;
	if (key == 65361) //right arrow
		gen->key->r = 0;
	if (key == 97)//A
		gen->key->a = 0;
	if (key == 100)//D
		gen->key->d = 0;
	if (key == 119)//W
		gen->key->w = 0;
	if (key == 115)//S
		gen->key->s = 0;
	return (0);
}
