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
	player.vector_len = 100;
	player.dirx = 0;
	player.diry = -1;
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
	int end_px = player->px + player->vector_len * player->dirx;
	int end_py = player->py + player->vector_len * player->diry;
	draw_line(img, player->px, player->py, end_px, end_py, 0x1F51FFFF); 
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
   double rotation = 0.1;

   if (keycode == ARROW_DOWN) {
        // Move backward without rotation
        player_move(&(frame->player), -movespeed);
    } else if (keycode == ARROW_UP) {
        // Move forward without rotation
        player_move(&(frame->player), movespeed);
    } else if (keycode == ARROW_LEFT) {
        // Rotate left without moving
        rotate_vector(&(frame->player), -rotation);
    } else if (keycode == ARROW_RIGHT) {
        // Rotate right without moving
        rotate_vector(&(frame->player), rotation);
    }
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