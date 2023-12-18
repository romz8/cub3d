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

void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
    while (1) {
        fill_pxl_mlx(img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { /* e_xy+e_x > 0 */
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) { /* e_xy+e_y < 0 */
            err += dx;
            y0 += sy;
        }
    }
}

void	map_render(char **map, t_frame *frame)
{
	int i;
	int	j;

	clear_screen(frame);
	i = 0;
	while (i < frame->map_w)
	{
		j = 0;
		while (j < frame->map_h)
		{
			if (map[j][i] != 0)
				draw_cube(frame, i * frame->map_scale, j * frame->map_scale, 0xFF00FFFF);
			else
			 	draw_cube(frame, i * frame->map_scale , j * frame->map_scale , 0x00000000);
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
				if ((x >= 0 && x < WIDTH)  && (y >= 0 && y < LENGTH))
				{
					if ((x > x_start && x < x_start + 63) && (y > y_start && y < y_start + 63))
						fill_pxl_mlx(&(frame->img), x, y, color);
                	else
                    	fill_pxl_mlx(&(frame->img), x, y, 0xFFFFFF);
				}
			x++;
		}
		y++;
	}
}