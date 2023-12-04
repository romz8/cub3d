/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:39:16 by rjobert           #+#    #+#             */
/*   Updated: 2023/11/29 11:39:19 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_hook(int keycode, t_frame *frame);

int main(void)
{
	t_frame	frame;
	t_img	img;
	t_player player;
	

	frame.mlx = mlx_init();
	frame.mlx_wdw = mlx_new_window(frame.mlx, WIDTH, LENGTH, "Cub3D");
	img.img = mlx_new_image(frame.mlx, WIDTH, LENGTH);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	frame.img = img;
	frame.map_scale = fmin(WIDTH / mapW, LENGTH / mapH);
	
	player.px = WIDTH/2;
	player.py = LENGTH/2;
	player.dirx = -1;
	player.diry = 1;
	frame.player = player;
	
	
	draw_player(&player, &img, &frame);
	mlx_key_hook(frame.mlx_wdw, key_hook, &frame);
	mlx_hook(frame.mlx_wdw, 17, 0, close_handler, &frame);
	mlx_loop(frame.mlx);
}

void	fill_pxl_mlx(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
	return;
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
	map_render(worldMap, frame);
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
		
		int ray_len = (int) ray_cast(frame, rayDirX, rayDirY);
		int end_px = player->px + ray_len * rayDirX;
		int end_py = player->py + ray_len * rayDirY;
		draw_line(img, player->px, player->py, end_px, end_py, 0x1F51FFFF);
	}
	draw_line(img, px, py, px + ray_cast(frame, dirx, diry) * dirx, py + ray_cast(frame, dirx, diry) * diry, 0xF70D1AFF);
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, img->img, 0, 0);
}

//cheeky event functions
int	esc_hook(int keycode, t_frame *frame)
{
	if (keycode == 53)
	{
		mlx_destroy_window(frame->mlx, frame->mlx_wdw);
		exit (0);
	}
	return (0);
}

int	close_handler(t_frame *frame)
{
	mlx_destroy_window(frame->mlx, frame->mlx_wdw);
	exit (0);
}

void	player_move(t_player *player, float movespeed)
{
	player->px += player->dirx * movespeed;
	player->py += player->diry * movespeed;
}

void	rotate_vector(t_player *player, double angle)
{
	double old_dirx;
	double	old_diry;

	old_dirx = player->dirx;
	old_diry = player->diry;
	player->dirx = old_dirx * cos(angle) - old_diry * sin(angle);
	player->diry = old_dirx * sin(angle) + old_diry * cos(angle);
}
int	move(int keycode, t_frame *frame)
{
   double movespeed = 10;
   double rotation = 0.05;
   printf("we have dirx, diry =(%f, %f) before \n", frame->player.dirx, frame->player.diry);

	if (keycode == ARROW_DOWN)
   		player_move(&(frame->player), -movespeed);
	else if (keycode == ARROW_UP)
        player_move(&(frame->player), movespeed); 
	else if (keycode == ARROW_LEFT)
        rotate_vector(&(frame->player), -rotation);
    else if (keycode == ARROW_RIGHT)
        rotate_vector(&(frame->player), rotation);
	printf("we have dirx, diry =(%f, %f) after \n", frame->player.dirx, frame->player.diry);
	draw_player(&(frame->player), &(frame->img), frame);
    return (0);
}

int key_hook(int keycode, t_frame *frame)
{
	if (keycode == 53)
		esc_hook(keycode, frame);
	else
		move(keycode, frame);
	return (0);
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

double	ray_cast(t_frame *frame, double dirx, double diry)
{
	int mapx;
	int mapy;
	int stepx;
	int stepy;
	int	hit;
	int	side;
	double side_distx;
	double	delta_distx;
	double side_disty;
	double	delta_disty;
	double wall_dist;

	mapx = (int) frame->player.px;
	mapy = (int) frame->player.py;
	
	if (dirx == 0)
		delta_distx =1e30;
	else
		delta_distx = fabs(1 / dirx);
	if (diry == 0)
		delta_disty =1e30;
	else
		delta_disty = fabs(1 /diry);
	
	if (dirx < 0)
	{
		stepx = -1;
		side_distx = (frame->player.px - mapx) * delta_distx;
	}
	else
	{
		stepx = 1;
		side_distx = (mapx + 1.0 - frame->player.px) * delta_distx;
	}
	if (diry < 0)
	{
		stepy = -1;
		side_disty = (frame->player.py - mapy) * delta_disty;
	}
	else
	{
		stepy = 1;
		side_disty = (mapy + 1.0 - frame->player.py) * delta_disty;
	}
	//printf("parameter are px,py = (%f, %f) mappx,mapy = (%i, %i) dirx,diry = (%f, %f), side_dx, side_dy = (%f, %f) delta_sidex, delt_sidey = (%f, %f)", frame->player.px, frame->player.py, mapx, mapy, frame->player.dirx, frame->player.diry, side_distx, side_disty, delta_distx, delta_disty);
	hit = 0;
	while (hit == 0)
	{
		if (side_distx < side_disty)
		{
			side_distx += delta_distx;
			mapx += stepx;
			side = 0;
		}
		else
		{
			side_disty += delta_disty;
			mapy += stepy;
			side = 1;
		}
		if (worldMap[mapx / frame->map_scale][mapy / frame->map_scale] > 0)
			hit = 1;
	}
		if (side == 0)
		wall_dist = (mapx - frame->player.px + (1 - stepx) / 2) / dirx;
	else
		wall_dist = (mapy - frame->player.py + (1 - stepy) / 2) / diry;	
	return (wall_dist);
}