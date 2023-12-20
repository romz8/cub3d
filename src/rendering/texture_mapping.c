/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:35:55 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/08 11:36:09 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
find which coordinate is the wall exposed to. 
If we are hitting a vertical side of the wall (side = 1)
and we are looking up (diry < 0) , the side of the wall is 
exposed to NORTH, otherwise SOUTH
if we are hitting a horizontal side of the wall on the array (side = 0)
and we are looking east (dirX > 0) this side is exposed EAST, 
otherwise WEST
then NORTH, SOUTH, WEST, EAST correspond to array of saved texture.
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

/**
 * Calculates the horizontal texture coordinate (textx) based on the ray's 
 * intersection with a wall.
 *
 * @param frame A pointer to the frame structure containing player and 
 * raycasting information.
 * @param ray A pointer to the ray structure containing information about the 
 * raycast.
 *
 * This function determines the exact horizontal position (wallx) where the ray 
 * intersects a wall. 
 * The position is normalized between 0 and 1 and then scaled by the size of the 
 * texture to find the
 * corresponding texture x-coordinate (textx). The function adjusts textx if the 
 * ray hits the left or 
 * right side of a wall to correctly orient the texture.
 */
void	locate_textx(t_frame *frame, t_ray *ray)
{
	double	wallx;

	if (ray->side == 0)
		wallx = frame->player.py + ray->wall_dist * ray->ray_diry;
	else
		wallx = frame->player.px + ray->wall_dist * ray->ray_dirx;
	wallx -= floor(wallx);
	ray->textx = (int)(wallx * (double) BMAP_SIZE);
	if (ray->side == 0 && ray->ray_dirx < 0)
		ray->textx = BMAP_SIZE - ray->textx - 1;
	if (ray->side == 1 && ray->ray_diry > 0)
		ray->textx = BMAP_SIZE - ray->textx -1;
}

/**
 * Retrieves the color of a specific pixel from the loaded texture.
 *
 * @param frame A pointer to the frame structure containing the 
 * loaded texture.
 * @param ray A pointer to the ray structure containing texture coordinates.
 * @return The color of the pixel in the texture at the specified coordinates.
 *
 * This function calculates the memory address of the pixel in the texture 
 * using the ray's texture 
 * coordinates (texty and textx). It then returns the color value of the pixel 
 * at that address.
 */
int	pix_bitmap(t_frame *frame, t_ray *ray)
{
	char	*pxl;
	t_img	*img;

	if (frame->load_scss[ray->wall_type] == 1)
	{
		img = &frame->loaded_texture[ray->wall_type];
		pxl = img->addr + (ray->texty * img->line_len + ray->textx * \
		(img->bits_per_pixel / 8));
		return (*(int *) pxl);
	}
	else
		return (frame->bckup_clr[ray->wall_type]);
}

/**
 * Renders a vertical slice of a wall based on a ray's intersection.
 *
 * @param x The x-coordinate on the screen where the wall slice should 
 * be drawn.
 * @param ray A pointer to the ray structure containing information about 
 * the raycast.
 * @param frame A pointer to the frame structure containing rendering 
 * information.
 *
 * This function calculates the vertical slice of a wall to be rendered based 
 * on a ray's intersection point.
 * It determines how much to increment the texture coordinate for each 
 * pixel on the screen and then loops
 * through each pixel in the slice. For each pixel, it calculates the
 * appropriate 
 * texture y-coordinate, 
 * fetches the corresponding color from the texture, and draws it on the screen. 
 * It also applies shading 
 * for Y-axis-aligned walls to create depth perception. The pixels above 
 * and below the wall slice are filled
 * with ceiling and floor colors, respectively.
 */
void	wall_to_texture(int x, t_ray *ray, t_frame *frame)
{
	double	step;
	double	text_pos;
	int		y;
	int		color;

	step = (float) BMAP_SIZE / ray->w_height;
	text_pos = (ray->w_start - LENGTH / 2 + ray->w_height / 2) * step;
	locate_textx(frame, ray);
	y = 0;
	while (y < ray->w_start)
		fill_pxl_mlx(&(frame->img), x, y++, frame->ceiling_color);
	while (y < ray->w_end)
	{
		ray->texty = (int) text_pos & (BMAP_SIZE - 1);
		text_pos += step;
		color = pix_bitmap(frame, ray);
		fill_pxl_mlx(&(frame->img), x, y, color);
		y++;
	}
	while (y < LENGTH)
		fill_pxl_mlx(&(frame->img), x, y++, frame->floor_color);
}
