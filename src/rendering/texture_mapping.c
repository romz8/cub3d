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
void	load_bckup_wall(t_frame *frame);
void	load_texture(t_frame *frame)
{
	t_img	img;
	//char *path[4] = {"./assets/north.xpm", "./assets/south.xpm", "./assets/weast.xpm", "./assets/east.xpm"}; //to replace by struct later on
	char *path[4] = {"./assets/wood.xpm", "./assets/eagle.xpm", "./assets/redbrick.xpm", "./assets/purplestone.xpm"}; //to replace by struct later on
	int	i;

	load_bckup_wall(frame);
	i = 0;
	while (i < 4)
	{
		img = frame->loaded_texture[i];
		img.img = mlx_xpm_file_to_image(frame->mlx, path[i], &img.img_w, &img.img_h);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
		if (!img.addr || !img.img_w || !img.img_h || img.img_h != BMAP_SIZE \
		|| img.img_w != BMAP_SIZE)
		{
			printf("Asset image not loaded, replaced by wall backup\n");
			frame->load_scss[i] = 0;
		}
		else
		{
			frame->loaded_texture[i] = img;
			frame->load_scss[i] = 1;
		}
		i++;
	}
}

void	load_bckup_wall(t_frame *frame)
{
	frame->bckup_clr[0] = 0x00FF0000;
	frame->bckup_clr[1] = 0x0000FF00;
	frame->bckup_clr[2] = 0x000000FF;
	frame->bckup_clr[3] = 0x00FF00FF;
}

void	load_sprite(t_frame *frame)
{
	t_img	*img;
	char	*path[5];
	int		i;

	path[0] = "./assets/sprite/w3dfps1.xpm";
	path[1] = "./assets/sprite/w3dfps2.xpm";
	path[2] = "./assets/sprite/w3dfps2.xpm";
	path[3] = "./assets/sprite/w3dfps2.xpm";
	path[4] = "./assets/sprite/w3dfps2.xpm";
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
 * coordinates (texty and textx). It then returns the color value of the pixel at
 *  that address.
 */
int	pix_bitmap(t_frame *frame, t_ray *ray)
{
	char	*pxl;
	t_img	*img;

	if (frame->load_scss[ray->wall_type] == 1)
	{
		img = &frame->loaded_texture[ray->wall_type];
		pxl = img->addr + (ray->texty * img->line_len + ray->textx * (img->bits_per_pixel / 8));
		return (*(int *) pxl);
	}
	else
		return (frame->bckup_clr[ray->wall_type]);
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
