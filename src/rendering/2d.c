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
	int	i;
	int	j;

	i = 0;
	while (i < frame->map_w)
	{
		j = 0;
		while (j < frame->map_h)
		{
			if (map[j][i] == '1')
				draw_cube(frame, i * frame->map_scale, j * frame->map_scale, \
				0x00000000);
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
			if ((x - 1 >= 0 && x + 1 < WIDTH) && (y - 1 >= 0 && y + 1 < LENGTH))
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

/*
receive frame input and add a map on to the image instance
1. set up the scale as ratio between the screen and the map :
we take min (as we need to handle square and rectangle) of 
WIDTH or LENGTH of screen divided by 4 times the map grid size.
if the map is 5,5 and the screen width 1280x740, we will display
the map as (5,5) * min(1280 / 5 * 4 , 740 / 5 * 4) = 37 
so the map will be displayed as 185x185 pxl on our screen.
if the map would have been 40,40, it would be 4.6 so we would 
have a 184x184pxl minimap as well - same if the map would be
2000x2000 (taller than screen)
then we draw cubes (the map by rendering filled scare)
and the re-scaled player position in the map inred
*/
void	mini_map(t_frame *frame)
{
	int	px;
	int	py;
	int	scalex;
	int	scaley;

	scalex = WIDTH / (4 * frame->map_w);
	scaley = LENGTH / (4 * frame->map_h);
	frame->map_scale = fmin(scalex, scaley);
	px = frame->player.px * frame->map_scale;
	py = frame->player.py * frame->map_scale;
	map_render(frame->game_map, frame);
	draw_cube(frame, px, py, 0x00FF0000);
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->img.img, 0, 0);
}
