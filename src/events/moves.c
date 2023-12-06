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

void	player_move(t_frame *frame, float movespeed)
{
	double new_posx;
	double new_posy;
	t_player	*player;
	
	player = &(frame->player);
	new_posx = player->px + player->dirx * movespeed;
	new_posy = player->py + player->diry * movespeed;
	if (new_posx < 0 || new_posx > mapW)
		return;
	if (new_posy < 0 || new_posy > mapH)
		return;
	if(frame->game_map[(int) new_posy][ (int) new_posx] != 0)
		return;
	player->px += player->dirx * movespeed;
	player->py += player->diry * movespeed;
}

void	rotate_vector(t_player *player, double angle)
{
	double old_dirx;
	double	old_diry;
	double	old_planeX;

	old_dirx = player->dirx;
	old_diry = player->diry;
	old_planeX = player->planeX;
	player->dirx = old_dirx * cos(angle) - old_diry * sin(angle);
	player->diry = old_dirx * sin(angle) + old_diry * cos(angle);
	player->planeX = player->planeX * cos(angle) - player->planeY * sin(angle);
	player->planeY = old_planeX * sin(angle) + player->planeY * cos(angle);
}
int	move(int keycode, t_frame *frame)
{
   double movespeed = 0.5;
   double rotation = 0.05;

	if (keycode == ARROW_DOWN)
   		player_move(frame, movespeed);
	else if (keycode == ARROW_UP)
        player_move(frame, -movespeed); 
	else if (keycode == ARROW_LEFT)
        rotate_vector(&(frame->player), rotation);
    else if (keycode == ARROW_RIGHT)
        rotate_vector(&(frame->player), -rotation);
	draw_player(frame);
    return (0);
}

