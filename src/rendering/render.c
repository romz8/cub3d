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

void	map_render(int map[mapW][mapH], t_frame *frame)
{
	int i;
	int	j;

	clear_screen(frame);
	i = 0;
	while (i < mapW)
	{
		j = 0;
		while (j < mapH)
		{
			if (map[j][i] != 0)
				draw_cube(frame, i * frame->map_scale, j * frame->map_scale, WALL_COLOR);
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

void	draw_player(t_player *player, t_img *img, t_frame *frame)
{
	int	px, py;
	int	i,j;
	
	px = player->px;
	py = player->py;
	double dirx = player->dirx;
	double diry = player->diry;
	map_render(frame->game_map, frame);
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < LENGTH)
		{
			if ((px - 3 < i) && (i < px + 3) && (py - 3 < j) && ( j< py + 3))
				fill_pxl_mlx(img, i, j, 0xFFFF00);
			j++;
		}
		i++;
	}
	double FOV_scale = 0.66;
	double planeX = diry * FOV_scale; // FOV_scale determines the FOV width
	double planeY = -dirx * FOV_scale;
	for (int i = 0; i  < WIDTH ; i++) 
	{
    	double cameraX = 2 * i / (double)WIDTH - 1; // x-coordinate in camera space
    	double rayDirX = dirx + planeX * cameraX;
    	double rayDirY = diry + planeY * cameraX;
		t_ray ray;
		ray.ray_dirx = rayDirX;
		ray.ray_diry = rayDirY;
		int ray_len = (int) ray_cast(frame, &ray);
		int end_px = player->px + ray_len * rayDirX;
		int end_py = player->py + ray_len * rayDirY;
		draw_line(img, player->px, player->py, end_px, end_py, 0x1F51FFFF);
	}
	t_ray centre_ray;
	centre_ray.ray_dirx = dirx;
	centre_ray.ray_diry = diry;
	draw_line(img, px, py, px + ray_cast(frame, &centre_ray) * dirx, py + ray_cast(frame, &centre_ray) * diry, 0xF70D1AFF);
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, img->img, 0, 0);
}

void	fill_pxl_mlx(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
	return;
}