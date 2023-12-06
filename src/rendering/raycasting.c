/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:39:03 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/06 11:39:06 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_dist_setup(t_ray *ray, t_frame *frame);

void	init_ray(t_ray *ray, t_frame *frame)
{
	ray->mapx = (int) frame->player.px;
	ray->mapy = (int) frame->player.py;
	if (ray->ray_dirx == 0)
		ray->delta_distx =1e30;
	else
		ray->delta_distx = fabs(1 / ray->ray_dirx);
	if (ray->ray_diry == 0)
		ray->delta_disty =1e30;
	else
		ray->delta_disty = fabs(1 / ray->ray_diry);
	ray_dist_setup(ray, frame);
}

void	ray_dist_setup(t_ray *ray, t_frame *frame)
{
	if (frame->player.dirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (frame->player.px - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (ray->mapx + 1.0 - frame->player.px) * ray->delta_distx;
	}
	if (frame->player.diry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (frame->player.py - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (ray->mapy + 1.0 - frame->player.py) * ray->delta_disty;
	}
}

int	dda_algo(t_ray *ray, t_frame *frame)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->mapx += ray->stepx;
			side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->mapy += ray->stepy;
			side = 1;
		}
		if (frame->game_map[ray->mapy / frame->map_scale][ray->mapx / frame->map_scale] > 0)
			hit = 1;
	}
	return (side);
}

double	ray_cast(t_frame *frame, t_ray *ray)
{

	int	side;
	double wall_dist;

	init_ray(ray, frame);
	side = dda_algo(ray, frame);
	if (side == 0)
		wall_dist = (ray->side_distx  - ray->delta_distx);
	else
		wall_dist = (ray->side_disty  - ray->delta_disty);
	return (wall_dist);
}