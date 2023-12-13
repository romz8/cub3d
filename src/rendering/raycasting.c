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

/*
Configures a ray based on the player's current position and direction.
x is the screen column for which the ray is being cast.
camera_x calculates the x-coordinate on the camera plane, scaled from -1 
to 1, based on the screen width.
ray_dirx and ray_diry are the direction vectors of the ray, computed using 
the player's direction and the camera plane's x coordinates.
delta_distx and delta_disty represent the distance the ray has to travel 
to cross one x or y grid cell, calculated as the reciprocal of ray_dirx and ray_diry.
*/
void	setup_ray(t_ray *ray, t_frame *frame, int x)
{
	t_player *player;

	player = &frame->player;
	ray->mapx = (int) player->px;
	ray->mapy = (int) player->py;
	ray->camera_x = 2 * x / (double) WIDTH - 1;
	ray->ray_dirx = player->dirx + player->plane_x * ray->camera_x;
	ray->ray_diry = player->diry + player->plane_y * ray->camera_x;
	if (ray->ray_dirx == 0)
		ray->delta_distx =1e30;
	else
		ray->delta_distx = fabs(1 / ray->ray_dirx);
	if (ray->ray_diry == 0)
		ray->delta_disty =1e30;
	else
		ray->delta_disty = fabs(1 / ray->ray_diry);
	//printf("we have a player with px, py = %f, %f and planex, planey = %f. %f and dirx, diry = %f, %f", frame->player.px, frame->player.py, frame->player.plane_x, frame->player.plane_y, frame->player.dirx, frame->player.diry);
	//printf("mapx,mapy= %i, %i dirx, diry = %f, %f deltax, deltay= %f, %f \n", ray->mapx, ray->mapy, ray->ray_dirx, ray->ray_diry, ray->delta_distx, ray->delta_disty);
}
/*
Determines the step direction (stepx, stepy) and initial side distances
(side_distx, side_disty) for the ray.
This setup is used in the Digital Differential Analysis (DDA) algorithm
for grid traversal.
*/
void	ray_dist_setup(t_ray *ray, t_frame *frame)
{
	if (ray->ray_dirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (frame->player.px - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (ray->mapx + 1.0 - frame->player.px) * ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (frame->player.py - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (ray->mapy + 1.0 - frame->player.py) * ray->delta_disty;
	}
	//printf("in distsetp we have mapx = %i \n", ray->mapx);
}

/*
find which coordinate is the wall exposedo. 
If we are hitting a vertical side of the wall (side = 1)
and we are looking up (diry < 0) , the side of the wall is 
exposed to NORTH, otherwise SOUTH
if we are hitting a horizontal side of the wall on the array (side = 0)
and we are looking east (dirX > 0) this side is exposed EAST, 
otherwise WEST
then NORHT, SOUTH, WEST, EAST correspond to arary of saved texture.
*/
void	get_wall_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dirx > 0)
			ray->wall_type = EAST;
		else if (ray->ray_dirx < 0)
			ray->wall_type = WEST;
	}
	else if (ray->side == 1)
	{
		if (ray->ray_diry < 0)
			ray->wall_type = NORTH;
		else if (ray->ray_diry > 0)
			ray->wall_type = SOUTH;
	}
}
/*
Implements the DDA algorithm to find the first wall hit by the ray.
The ray's grid position (mapx, mapy) is updated until a wall is encountered.
side determines if the wall is hit on its x-side or y-side, affecting shading.
*/
void	dda_execute(t_ray *ray, t_frame *frame)
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
		if (frame->game_map[ray->mapy][ray->mapx] > 0)
			hit = 1;
	}
	ray->side = side;
	get_wall_texture(ray);
}

/*
Calculates the perpendicular distance of the wall from the player (wall_dist), 
avoiding fisheye distortion by using Euclidien distance
Determines the height of the wall slice (w_height) to be drawn on the screen.
Calculates the start (w_start) and end (w_end) positions on the screen for the 
wall slice (we will draw wall slice by slice, each slice being the x-coordinate 
cameraX and y being the wall height)
*/
void	wall_height(t_ray *ray)
{
	//printf("at wall_height we side_distx, side_disty = %f, %f\n", ray->side_distx, ray->side_disty);
	if (ray->side == 0)
		ray->wall_dist = (ray->side_distx  - ray->delta_distx);
	else
		ray->wall_dist = (ray->side_disty  - ray->delta_disty);
	if (ray->wall_dist < 0.03)
		ray->wall_dist = 0.03;
	ray->w_height = (int) LENGTH / ray->wall_dist;
	ray->w_start = (LENGTH / 2) - (ray->w_height / 2);
	ray->w_end = (LENGTH / 2) + (ray->w_height / 2);
	if (ray->w_start < 0)
		ray->w_start = 0;
	if (ray->w_end >= LENGTH)
		ray->w_end = LENGTH - 1;
	//printf("at wall_height we w_start, w_end = %i, %i\n", ray->w_start, ray->w_end);
}

/*
The main loop of the raycasting engine, executed for each column of the screen.
Calls the functions above to calculate and render each ray's wall slice.
*/
int	raycasting(t_frame *frame)
{
	int	x;
	t_ray ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray);
		setup_ray(&ray, frame, x);
		ray_dist_setup(&ray, frame);
		dda_execute(&ray, frame);
		wall_height(&ray);
		//render_wall_slice(frame, x, ray.w_start, ray.w_end, color_ray(&ray));
		wall_to_texture(x, &ray, frame);
		x++;
	}
	//printf("player position is px,py = %f, %f and mapx, mapy = %i, %i\n", frame->player.px, frame->player.py, ray.mapx, ray.mapy);
	return (1);
}