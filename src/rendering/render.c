/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:41:37 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/06 11:41:39 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color);
void	render_plane(t_frame *frame);
int		color_ray(t_ray *ray);

void	clear_screen(t_frame *frame)
{
	int x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < LENGTH)
		{
			fill_pxl_mlx(&(frame->img), x, y, 0x00000000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->img.img, 0, 0);
}

void	draw_player(t_frame *frame)
{
	clear_screen(frame);
	//mlx_destroy_image(frame->mlx, &(frame->img));
	render_plane(frame);
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->img.img, 0, 0);
}

void	fill_pxl_mlx(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
	return;
}

void	render_plane(t_frame *frame)
{
	double planeX;
	double planeY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	t_ray	ray;
	double	plane_dist;
	int	wall_height;
	int wslice_start;
	int wslice_end;
	int	i;

	planeX = frame->player.diry * FOV;
	planeY = -frame->player.dirx * FOV;
	i = 0;
	while (i < WIDTH)
	{
		cameraX = 2 * (i / (double) WIDTH) - 1;
		rayDirX = frame->player.dirx + planeX * cameraX;
    	rayDirY = frame->player.diry + planeY * cameraX;
		init_ray(&ray, frame, rayDirX, rayDirY);
		plane_dist = ray_cast(frame, &ray);
		wall_height = LENGTH / plane_dist;
		wslice_start = LENGTH / 2 - wall_height / 2;
		wslice_end = LENGTH / 2 + wall_height / 2;
		if (wslice_start < 0)
			wslice_start = 0;
		if (wslice_end > LENGTH)
			wslice_end = LENGTH - 1;
		draw_line(&(frame->img), i, wslice_start, i, wslice_end, color_ray(&ray));
		i++;
	}
}

void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color)
{
	int	y;

	y = slice_start;
	while (y < slice_end)
	{
		fill_pxl_mlx(&(frame->img), x, y, color);
		y++;
	}
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->img.img, 0, 0);
}

int	color_ray(t_ray *ray)
{
	int color;

	if (ray->wall_type == 1)
		color = 0x1F51FFFF;
	else if (ray->wall_type == 2)
		color = 0xFF7F50FF;
	else
		color = 0x32CD32FF;
	if (ray->side == 1)
		color /= 2;
	return (color);
}