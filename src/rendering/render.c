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
void	draw_player(t_frame	*frame, int	i);

int	render(t_frame *frame)
{ 
	raycasting(frame);
	mouse_event(frame);
	move(frame);
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->img.img, 0, 0);
	mini_map(frame);
	draw_player(frame, 0);
	return (1);
}

void	fill_pxl_mlx(t_img *img, int x, int y, int color)
{
	char	*dst;

	
	if (x < 0 || x > WIDTH || y < 0 || y > LENGTH)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
	return;
}
/*
to render a wall with one colour (colour each pxl with one color)
*/
void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color)
{
	int	y;

	y = slice_start;
	while (y < slice_end)
	{
		fill_pxl_mlx(&(frame->img), x, y, color);
		y++;
	}
}

void	draw_player(t_frame	*frame, int	i)
{
	int adx;

	adx = 4;
	if (i == 0)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->sprite[i].img, WIDTH/2 - 65, LENGTH - 175);
	if (i == 1)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->sprite[i].img, WIDTH/2 - 65 + adx, LENGTH - 210);
	else if (i == 2)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->sprite[i].img, WIDTH/2 - 65 + adx, LENGTH - 210);
	else if (i == 3)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->sprite[i].img, WIDTH/2 - 65 + adx, LENGTH - 210);
	else if (i == 4)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->sprite[i].img, WIDTH/2 - 65 + adx, LENGTH - 210);
}