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
  bool  found_map;
	bool  space_found;
}	t_map;

typedef enum s_texture_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	UNKNOWN
}	t_texture_type;

typedef struct s_cardinal
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	char		*floor;
	char		*ceil;
}	t_cardinal;

typedef struct s_textures
{
	t_texture_type	type;
	char			*path;
	char			*texture_raw;
	char			**info;
	t_cardinal		*paths;
	bool			path_found;
}	t_textures;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	unsigned int	hex;
}	t_color;

typedef struct s_map_color
{
	t_color		*floor_color;
	t_color		*ceil_color;
}	t_map_color;

/* ====== init functions ===================================*/
void  init_player(t_frame *frame, t_player *player, t_map *map);
void	init_ray(t_ray *ray);
void  free_map(t_frame *frame);
void free_loader(t_map	*map);

/*====== rendering functions ================================*/
int   render(t_frame *frame);
void	draw_coord(t_frame *frame);
void	mini_map(t_frame *frame);
void	fill_pxl_mlx(t_img *img, int x, int y, int color);
void	clear_screen(t_frame *frame);
void	draw_player(t_frame	*frame, int	i);

/*======= Raycasting Engine ==================================*/
int   raycasting(t_frame *frame);
void	render_wall_slice(t_frame *frame, int x, int slice_start, int slice_end, int color);
int	  color_ray(t_ray *ray);
void	get_wall_texture(t_ray *ray);
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

//color.c
t_map_color		init_color(t_map_color *color);
void			get_color_floor(t_map_color *color, t_textures *texture);
void			get_color_ceil(t_map_color *color, t_textures *texture);
void			ft_check_color(t_map_color *color);
unsigned int	create_hex_color(int r, int g, int b);
void			free_colors(char **char_numbers);
int	create_hex_trgb(int t, int r, int g, int b);

//aux_color.c
bool			is_numeric(const char *str);
int				ft_atoi(const char *str);
bool			is_color(int color);
void			ft_check_color(t_map_color *color);

// free_colors.c
void			ft_free_colors(t_map_color *color);
void			free_colors(char **col);

//check parameters
bool	ft_check_nbr_arguments(int argc);
bool	ft_check_extension(char **argv);
void	ft_check_parameters(int argc, char **argv);
//launch_and_free.c
void	ft_free_map(t_map *map);
void	ft_read_cub(char **argv, t_textures *text, t_map *map);
t_map	ft_start_map(char **argv);


// map.c
t_map	init_map(t_map *map);
void	create_2d(t_map *map);
void	handle_slash_en(int *y, int *k, int *x);
void	copy_line_to_map(t_map *map);

// read_map.c
bool    is_empty_or_spaces(char *line);
void    process_map_line(t_map *map, char *line, int *line_number);
void	set_measures_and_close(t_map *map, int line_number, int fd);
void 	ft_read_map(char** argv, t_map *map);
void    print_filled_map(t_map *map);

// aux_maps.c
// // Funciones de libft y el write error con mensaje
void	ft_write_error(char *message);
void	ft_write(char *message);
bool    ft_strcmp(char *s1, char *s2);
bool    ft_check_comas(char *input);
char	*ft_strndup(char *s1, size_t len);

// check_lines.c
	// Funciones para asegurar que la linea es de mapa y ver que linea es la mas ancha
bool	is_map_char(char c);
bool	skip_whitespace(char *line, int *length);
bool	is_valid_map_line(char *line);
bool	is_valid_line_inside(char *line);

// get_next_line
char	*get_next_line(int fd);
int		count_line_words(char *str);
void	clean_storage(char *storage);
char	*extract_line(char *str);
// get_next_line2.c
char	*ft_strchr(const char *s, int c);
char	*free_malloc(char *str);
int		contain_line(char *str);
int		get_storage_len(char *storage);
char	*concat_str(char *storage, char *buffer, int len_b);

//init_textures.c
bool			  are_texture_paths_filled(t_cardinal *paths);
t_textures  init_textures(t_textures *texture);
void        free_textures(t_textures *texture);
void        free_mapcolor(t_map_color  *color);

// read_textures.c
void			get_texture_type(t_textures *texture, char *info, char **paths);
void			ft_free_paths(char **paths);
void			process_texture_raw(t_textures *texture);
bool			only_map_chars(char *line);
void			process_textures(t_textures *texture, char *line);

//player.c
// t_player	*init_player(void);
void  get_player(t_map *map);
void  get_player_direction(t_map *map, int y, int x);
bool  is_space_around(t_map *map, int x, int y);
bool  check_map(t_map *map);

#endif