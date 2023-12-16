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
	if (new_posx < 0 || new_posx > frame->map_w)
		return;
	if (new_posy < 0 || new_posy > frame->map_h)
		return;
	if(frame->game_map[(int) new_posy][ (int) new_posx] != '0')
		return;
	player->px = new_posx;
	player->py = new_posy;
}

void	player_side_move(t_frame *frame, float movespeed)
{
	double new_posx;
	double new_posy;
	t_player	*player;
	
	player = &(frame->player);
	new_posx = player->px - player->diry * movespeed;
	new_posy = player->py + player->dirx * movespeed;
	if (new_posx < 0 || new_posx > frame->map_w)
		return;
	if (new_posy < 0 || new_posy > frame->map_h)
		return;
	if(frame->game_map[(int) new_posy][ (int) new_posx] != '0')
		return;
	player->px = new_posx;
	player->py = new_posy;
}
	

void	rotate_vector(t_frame *frame, double angle)
{
	double old_dirx;
	double	old_planex;
	t_player	*player;

	player = &frame->player;
	old_dirx = player->dirx;
	old_planex = player->plane_x;
	player->dirx = player->dirx * cos(angle) - player->diry * sin(angle);
	player->diry = old_dirx * sin(angle) + player->diry * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_planex * sin(angle) + player->plane_y * cos(angle);
}

int	move(t_frame *frame)
{
   double movespeed = 0.05;
   double rotation = 0.02;

	if (frame->player.key.up == 1)
   		player_move(frame, movespeed);
	else if (frame->player.key.down == 1)
        player_move(frame, -movespeed);
	if (frame->player.key.left == 1)
        player_side_move(frame, -movespeed);
	else if (frame->player.key.right == 1)
        player_side_move(frame, movespeed);
	if (frame->player.key.rotate_l == 1)
        rotate_vector(frame, -rotation);
    else if (frame->player.key.rotate_r == 1)
        rotate_vector(frame, rotation);
    return (0);
}

