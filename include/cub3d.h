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
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1280
#define LENGTH 720
#define mapW 24
#define mapH 24
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define FOV 0.66
# define  BMAP_SIZE 64

enum e_texture {
  NORTH,
  SOUTH,
  WEST,
  EAST
} ;

typedef struct	s_img 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
  int   img_w;
  int   img_h;
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
  char  direction;
  int   map_scale;
  int   (*game_map)[mapW];
  t_img loaded_texture[4];
  int   ceiling_color;
  int   floor_color;
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
  int  textx;
  int  texty;
} t_ray;

/* ====== init functions ===================================*/
void  init_player(t_frame *frame, t_player *player);
void	init_ray(t_ray *ray);

/*====== rendering functions ================================*/
int	draw_player(t_frame *frame);
void	fill_pxl_mlx(t_img *img, int x, int y, int color);
void	map_render(int map[mapW][mapH], t_frame *frame);
void	clear_screen(t_frame *frame);
void  draw_line(t_img *img, int x0, int y0, int x1, int y1, int color);

/*======= Raycasting Engine ==================================*/
int   raycasting(t_frame *frame);
void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color);
int	color_ray(t_ray *ray);
void	wall_to_texture(int x, t_ray *ray, t_frame *frame);
void	load_texture(t_frame *frame);

/*========= Events handlers =============================*/
int		esc_hook(int keycode, t_frame *frame);
int   close_handler(t_frame *frame);
int   key_hook(int keycode, t_frame *frame);
void	player_move(t_frame *frame, float movespeed);
void	rotate_vector(t_frame *frame, double angle);
int	move(int keycode, t_frame *frame);
int mouse_event(t_frame *frame);
void mouse_rotate(t_frame *frame, int x);


#endif