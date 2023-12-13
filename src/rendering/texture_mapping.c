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

void	load_texture(t_frame *frame)
{
	t_img	img;
	char *path[4] = {"./assets/wood.xpm", "./assets/colorstone.xpm", "./assets/redbrick.xpm", "./assets/greystone.xpm"}; //to replace by struct later on
	int	i;

	i = 0;
	while (i < 4)
	{
		img = frame->loaded_texture[i];
		img.img = mlx_xpm_file_to_image(frame->mlx, path[i], &img.img_w, &img.img_h);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
		if (!img.addr)
		{
			printf("Asset image not loaded\n"); 
			exit(EXIT_FAILURE); // to replace with error management
		}
		frame->loaded_texture[i] = img;
		i++;
	}
	frame->floor_color = 0x42424242;
	frame->ceiling_color = 0x00CEEBFF;
}

void	load_sprite(t_frame *frame)
{
	t_img	*img;
	char	*path[5];
	int		i;

	path[0] = "./assets/sprite/fps1.xpm";
	path[1] = "./assets/sprite/fps2.xpm";
	path[2] = "./assets/sprite/fps3.xpm";
	path[3] = "./assets/sprite/fps4.xpm";
	path[4] = "./assets/sprite/fps5.xpm";
	i = 0;
	while (i < 5)
	{
		img = &frame->sprite[i];
		img->img = mlx_xpm_file_to_image(frame->mlx, path[i], &img->img_w, &img->img_h);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_len, &img->endian);
		if (!img->addr)
		{
			printf("Asset sprite not loaded\n"); 
			exit(EXIT_FAILURE); // to replace with error management
		}
		frame->sprite[i] = *img;
		i++;
	}
}

/**
 * Calculates the horizontal texture coordinate (textx) based on the ray's 
 * intersection with a wall.
 *
 * @param frame A pointer to the frame structure containing player and raycasting 
 * information.
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
	double wallx;	

	if (ray->side == 0)
		wallx = frame->player.py + ray->wall_dist * ray->ray_diry;
	else
		wallx = frame->player.px+ ray->wall_dist * ray->ray_dirx;
	wallx -= floor(wallx);
	ray->textx = (int) (wallx * (double) BMAP_SIZE);
	if (ray->side == 0 && ray->ray_dirx > 0)
		ray->textx = BMAP_SIZE - ray->textx;
	if (ray->side == 1 && ray->ray_dirx < 0)
		ray->textx = BMAP_SIZE - ray->textx;
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
 * coordinates (texty and textx). It then returns the color value of the pixel at
 *  that address.
 */
int	pix_bitmap(t_frame *frame, t_ray *ray)
{
	char	*pxl;
	t_img	*img;

	img = &frame->loaded_texture[ray->wall_type];
	pxl = img->addr + (ray->texty * img->line_len + ray->textx * (img->bits_per_pixel / 8));
	return (*(int *) pxl);
}

/**
 * Renders a vertical slice of a wall based on a ray's intersection.
 *
 * @param x The x-coordinate on the screen where the wall slice should be drawn.
 * @param ray A pointer to the ray structure containing information about the 
 * raycast.
 * @param frame A pointer to the frame structure containing rendering information.
 *
 * This function calculates the vertical slice of a wall to be rendered based 
 * on a ray's intersection point.
 * It determines how much to increment the texture coordinate for each pixel on 
 * the screen and then loops
 * through each pixel in the slice. For each pixel, it calculates the appropriate 
 * texture y-coordinate, 
 * fetches the corresponding color from the texture, and draws it on the screen. 
 * It also applies shading 
 * for Y-axis-aligned walls to create depth perception. The pixels above and below 
 * the wall slice are filled
 * with ceiling and floor colors, respectively.
 */
void	wall_to_texture(int x, t_ray *ray, t_frame *frame)
{
	double step;
	double	text_pos;
	int		y;
	int color;
	
	step = (float) BMAP_SIZE / ray->w_height;
	text_pos = (ray->w_start - LENGTH / 2 + ray->w_height / 2) * step;
	locate_textx(frame, ray);
	y = 0;
	while (y < ray->w_start)
		fill_pxl_mlx(&(frame->img), x, y++, frame->ceiling_color);
	y = ray->w_start;
	while (y < ray->w_end)
	{
		ray->texty = (int) text_pos & (BMAP_SIZE - 1);
		text_pos += step;
		color = pix_bitmap(frame, ray);
		if (ray->side == 1)
			 color = (color >> 1) & 8355711;
		fill_pxl_mlx(&(frame->img), x, y, color);
		y++;
	}
	while (y < LENGTH)
		fill_pxl_mlx(&(frame->img), x, y++, frame->floor_color);
}
