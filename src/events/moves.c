/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:38:09 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/06 11:38:11 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_move(t_player *player, float movespeed)
{
	player->px += player->dirx * movespeed;
	player->py += player->diry * movespeed;
}

void	rotate_vector(t_player *player, double angle)
{
	double old_dirx;
	double	old_diry;

	old_dirx = player->dirx;
	old_diry = player->diry;
	player->dirx = old_dirx * cos(angle) - old_diry * sin(angle);
	player->diry = old_dirx * sin(angle) + old_diry * cos(angle);
}
int	move(int keycode, t_frame *frame)
{
   double movespeed = 10;
   double rotation = 0.05;
   printf("we have dirx, diry =(%f, %f) before \n", frame->player.dirx, frame->player.diry);

	if (keycode == ARROW_DOWN)
   		player_move(&(frame->player), -movespeed);
	else if (keycode == ARROW_UP)
        player_move(&(frame->player), movespeed); 
	else if (keycode == ARROW_LEFT)
        rotate_vector(&(frame->player), -rotation);
    else if (keycode == ARROW_RIGHT)
        rotate_vector(&(frame->player), rotation);
	printf("we have dirx, diry =(%f, %f) after \n", frame->player.dirx, frame->player.diry);
	draw_player(&(frame->player), &(frame->img), frame);
    return (0);
}

