/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:19:19 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/06 15:19:23 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
void	draw_cube(t_frame *frame, int x_start, int y_start, int color);

void	map_render(char **map, t_frame *frame)
{
	int i;
	int	j;

	i = 0;
	while (i < frame->map_w)
	{
		j = 0;
		while (j < frame->map_h)
		{
			if (map[j][i] == '1')
				draw_cube(frame, i * frame->map_scale, j * frame->map_scale, 0x00000000);
			j++;
		}
		i++;
	}
}

void	draw_cube(t_frame *frame, int x_start, int y_start, int color)
{
	int	x;
	int	y;

	y = y_start;
	while (y < y_start + frame->map_scale)
	{
		x = x_start;
		while (x < x_start + frame->map_scale)
		{
				if ((x - 1 >= 0 && x + 1 < WIDTH)  && (y - 1 >= 0 && y + 1 < LENGTH))
				{
						fill_pxl_mlx(&(frame->img), x + 1, y + 1, color);
						fill_pxl_mlx(&(frame->img), x + 1, y - 1, color);
						fill_pxl_mlx(&(frame->img), x - 1, y + 1, color);
						fill_pxl_mlx(&(frame->img), x - 1, y - 1, color);
				}
			x++;
		}
		y++;
	}
}


void	mini_map(t_frame *frame)
{
	int	px;
	int	py;

	frame->map_scale = 4;
	px = frame->player.px * frame->map_scale;
	py = frame->player.py * frame->map_scale;
	map_render(frame->game_map, frame);
	draw_cube(frame, px, py, 0xFFFF0000);
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->img.img, 0, 0);
}