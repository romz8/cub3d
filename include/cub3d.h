/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:38:57 by rjobert           #+#    #+#             */
/*   Updated: 2023/11/29 11:38:59 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

#include "../minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1280
#define LENGTH 720
#define mapW 24
#define mapH 24
# define ESC 53
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define WALL_COLOR 0xC0C0C0FF
# define FOV 0.66

typedef struct	s_img 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct player {
	double	px;
	double	py;
  double  dirx;
  double  diry;
  double  plane_x;
  double  plane_y;
}	t_player;

typedef struct s_frame {
	void	*mlx;
	void	*mlx_wdw;
	t_img	img;
	t_player	player;
  int   map_scale;
  int   (*game_map)[mapW];
}	t_frame;

typedef struct s_ray{
  double ray_dirx;
  double ray_diry;
  double camera_x;
  int mapx;
  int mapy;
  int stepx;
  int stepy;
  double  side_distx;
  double  side_disty;
  double  delta_distx;
  double  delta_disty;
  int   side;
  int   wall_type;
  double  wall_dist;
  int  w_height;
  int  w_start;
  int  w_end;
} t_ray;

void	draw_player(t_frame *frame);
void	fill_pxl_mlx(t_img *img, int x, int y, int color);
int		esc_hook(int keycode, t_frame *frame);
int   close_handler(t_frame *frame);
int   key_hook(int keycode, t_frame *frame);
void	player_move(t_frame *frame, float movespeed);
int	move(int keycode, t_frame *frame);
void	map_render(int map[mapW][mapH], t_frame *frame);
void	draw_cube(t_frame *frame, int x_start, int y_start, int color);
int   raycasting(t_frame *frame);
void	clear_screen(t_frame *frame);
void  draw_line(t_img *img, int x0, int y0, int x1, int y1, int color);

void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color);
int	color_ray(t_ray *ray);


#endif