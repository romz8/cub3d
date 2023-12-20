/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:11:24 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/12 19:11:26 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
init player direction verctor based on map setup. if palyer is facing North,
it is looking up (diry -1) and the plane should be perpendicular so the vector
dot product is zero. Opposite case for looking south
*/
void	init_player_ns(t_frame *frame, t_player *player)
{
	if (frame->direction == 'N')
	{
		player->dirx = 0;
		player->diry = -1;
		player->plane_x = FOV;
		player->plane_y = 0;
	}
	else if (frame->direction == 'S')
	{
		player->dirx = 0;
		player->diry = 1;
		player->plane_x = -FOV;
		player->plane_y = 0;
	}
}

/*
similar to init_north_south but the logic is on axis-x for East-West
*/
void	init_player_ew(t_frame *frame, t_player *player)
{
	if (frame->direction == 'E')
	{
		player->dirx = 1;
		player->diry = 0;
		player->plane_x = 0;
		player->plane_y = FOV;
	}
	else if (frame->direction == 'W')
	{
		player->dirx = -1;
		player->diry = 0;
		player->plane_x = 0;
		player->plane_y = -FOV;
	}
}

/*
initiliaze player based on position and direction of where it's looking
then set all key press commands to 0
*/
void	init_player(t_frame *frame, t_player *player, t_map *map)
{
	if (!map)
		return ;
	frame->direction = map->p_direction;
	if (frame->direction == 'N' || frame->direction == 'S')
		init_player_ns(frame, player);
	else if (frame->direction == 'W' || frame->direction == 'E')
		init_player_ew(frame, player);
	else
	{
		ft_putstr_fd("Error while loading direction \n", STDERR_FILENO);
		exit(EXIT_FAILURE); //see how to handle memory later on
	}
	player->px = map->p_pos[0];
	player->py = map->p_pos[1];
	player->key.up = 0;
	player->key.down = 0;
	player->key.left = 0;
	player->key.right = 0;
	player->key.rotate_l = 0;
	player->key.rotate_r = 0;
}

/*
initialize a ray structure to zero to avoid any garbage or leftovers data
in memory : necessary to prevent undefined behaviour
*/
void	init_ray(t_ray *ray)
{
	ray->ray_dirx = 0.0;
	ray->ray_diry = 0.0;
	ray->camera_x = 0.0;
	ray->mapx = 0;
	ray->mapy = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->side_distx = 0.0;
	ray->side_disty = 0.0;
	ray->delta_distx = 0.0;
	ray->delta_disty = 0.0;
	ray->side = 0;
	ray->wall_type = 0;
	ray->wall_dist = 0.0;
	ray->w_height = 0;
	ray->w_start = 0;
	ray->w_end = 0;
	ray->textx = 0;
	ray->texty = 0;
}
