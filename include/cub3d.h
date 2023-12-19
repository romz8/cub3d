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

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

# define WIDTH 1280
# define LENGTH 720
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
# define BUFFER_SIZE 1
# define TAB_SPACES 4

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

typedef struct s_keys
{
  int up;
  int down;
  int left;
  int right;
  int rotate_l;
  int rotate_r;
} t_keys;

typedef struct player 
{
	double	px;
	double	py;
  double  dirx;
  double  diry;
  double  plane_x;
  double  plane_y;
  t_keys  key;
}	t_player;


typedef struct s_frame {
	void	*mlx;
	void	*mlx_wdw;
	t_img	img;
	t_player	player;
  char  direction;
  float  map_scale;
  char  **game_map;
  int   map_w;
  int   map_h;
  t_img loaded_texture[4];
  t_img sprite[5];
  bool  load_scss[4];
  int   bckup_clr[4];
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

/*======== frank header ======================*/

typedef struct s_map
{
	char	*map_raw;
	char	**map_2d;
	int		max_height;
	int		max_width;
	int		map_start;
	int		map_end;
  char	p_direction;
  int		p_pos[2];
  int color_f[3];
  int color_c[3];
  char *texture[4];
}	t_map;

typedef enum {
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	UNKNOWN
} t_texture_type;

typedef struct s_cardinal
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*floor;
	char			*ceil;
}	t_cardinal;

typedef struct s_textures {
    t_texture_type	type;
    char			*path;
	char    		*texture_raw;
	char			**info;
	t_cardinal		*paths;
} t_textures;

/* ====== init functions ===================================*/
void  init_player(t_frame *frame, t_player *player, t_map *map);
void	init_ray(t_ray *ray);

/*====== rendering functions ================================*/
int   render(t_frame *frame);
void	draw_coord(t_frame *frame);
void	mini_map(t_frame *frame);
void	fill_pxl_mlx(t_img *img, int x, int y, int color);
// void	map_render(int map[mapW][mapH], t_frame *frame);
void	clear_screen(t_frame *frame);
void	draw_player(t_frame	*frame, int	i);

/*======= Raycasting Engine ==================================*/
int   raycasting(t_frame *frame);
void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color);
int	  color_ray(t_ray *ray);
void	wall_to_texture(int x, t_ray *ray, t_frame *frame);
void	load_texture(t_frame *frame, t_map *map);
void  load_sprite(t_frame *frame);

/*========= Events handlers =============================*/
int		esc_hook(int keycode, t_frame *frame);
int   close_handler(t_frame *frame);
int   key_hook_press(int keycode, t_frame *frame);
int key_hook_release(int keycode, t_frame *frame);
void	player_move(t_frame *frame, float movespeed);
void	rotate_vector(t_frame *frame, double angle);
int   move(t_frame *frame);
int   mouse_event(t_frame *frame);
void  mouse_rotate(t_frame *frame, int x);
int	sprite_hook(int	key_code, int x, int y, t_frame *frame);

/*===== FRANK REUNITE ====================== */

//color.
void	get_color_floor(t_map *map, t_textures *texture);
void	get_color_ceil(t_map *map, t_textures *texture);
void	        ft_check_color(t_map *map);
int	create_hex_trgb(int t, int r, int g, int b);

//aux_color.c
bool    is_numeric(const char *str);
int		ft_atoi(const char *str);

//check parameters
bool    ft_check_nbr_arguments(int argc);
bool    ft_check_extension(char **argv);
void    ft_check_parameters(int argc, char **argv);
t_map   *ft_start_map(char **argv);

// map.c
t_map	*init_map(void);
void	create_2d(t_map *map);
void    handle_slash_en(t_map *map, int *y, int *k, int *x);
void    handle_tabs(t_map *map, int y, int *x, int *k);
void    copy_line_to_map(t_map *map);

// read_map.c
bool    is_empty_or_spaces(char *line);
void    process_map_line(t_map *map, char *line, int *line_number);
int 	set_measures_and_close(t_map *map, int line_number, int fd);
void 	ft_read_map(char** argv, t_map *map);
void    print_filled_map(t_map *map);

// aux_maps.c
// // Funciones de libft y el write error con mensaje
void	ft_write_error(char *message);
void	ft_write(char *message);
bool    ft_strcmp(char *s1, char *s2);
bool    ft_check_comas(char *input);

// check_lines.c
	// Funciones para asegurar que la linea es de mapa y ver que linea es la mas ancha
bool    skip_whitespace(t_map *map, char *line, int *length, int *length_width);
void    start_map(t_map *map, int *length, int *length_width, bool *map_started);
void    process_other_chars(t_map *map, char *line, int *length,
		int *length_width);
bool    is_valid_map_line(char *line, t_map *map);
bool    is_valid_line_inside(char *line, t_map *map);

// get_next_line
char    *get_next_line(int fd);
char    *ft_read(int fd, char *ptr);
char    *ft_cutword(char *prt);
char    *ft_strchr(const char *s, int c);
char    *ft_substr_m(char const *s, unsigned int start, size_t len);

//init_textures.c
t_textures		*init_textures(void);

// read_textures
void    		ft_read_textures(char **argv, t_textures *texture);
void   		 	process_textures(t_textures *texture, char *line);
bool		    only_map_chars(char *line);
void		    process_texture_raw (t_textures *texture);
t_texture_type  get_texture_type(t_textures *texture, int index);

//player.c
// t_player	*init_player(void);
void		get_player(t_map *map);
void		get_player_direction(t_map *map, int y, int x);
bool		is_space_around(t_map *map, int x, int y);
bool		check_map(t_map *map);

#endif