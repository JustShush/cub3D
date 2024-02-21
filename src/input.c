/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiniz-m <ddiniz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:49:01 by ddiniz-m          #+#    #+#             */
/*   Updated: 2024/02/08 12:46:31 by ddiniz-m         ###   ########.fr       */
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
	if (key == 65363)
		gen->key->l = 1;
	if (key == 65361)
		gen->key->r = 1;
	if (key == 97)
		gen->key->a = 1;
	if (key == 100)
		gen->key->d = 1;
	if (key == 119)
		gen->key->w = 1;
	if (key == 115)
		gen->key->s = 1;
	return (0);
}

int	key_release(int key, t_general *gen)
{
	if (key == 65363)
		gen->key->l = 0;
	if (key == 65361)
		gen->key->r = 0;
	if (key == 97)
		gen->key->a = 0;
	if (key == 100)
		gen->key->d = 0;
	if (key == 119)
		gen->key->w = 0;
	if (key == 115)
		gen->key->s = 0;
	return (0);
}
