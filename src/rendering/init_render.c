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

void  init_player(t_frame *frame, t_player *player)
{
  if (frame->direction == 'N')
  {
    player->dirx = 0;
	  player->diry = -1;
  }
  else if (frame->direction == 'S')
  {
    player->dirx = 0;
	  player->diry = 1;
  }
  else if(frame->direction == 'E')
  {
    player->dirx = 1;
	  player->diry = 0;
  }
  else if(frame->direction == 'W')
  {
    player->dirx = -1;
	  player->diry = 0;
    player->plane_x = 0;
		player->plane_y = -0.66;
  }
  player->plane_x = player->diry * FOV;
  player->plane_y = -player->dirx * FOV;
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