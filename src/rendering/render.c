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
	raycasting(frame);
	//render_plane(frame);
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
	raycasting(frame);
}

void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color)
{
	int	y;

	
	printf("in printf we w_start, w_end = %i, %i\n", slice_start, slice_end);
	y = slice_start;
	while (y < slice_end)
	{
		fill_pxl_mlx(&(frame->img), x, y, color);
		y++;
	}
}

int	color_ray(t_ray *ray)
{
	int color;

	if (ray->wall_type == 1)
		color = 0x1F51FFFF;
	else
		color = 0x32CD32FF;
	// if (ray->wall_type == 2)
	// 	color = 0x32CD32FF;
	if (ray->side == 1)
		color /= 2;
	return (color);
}