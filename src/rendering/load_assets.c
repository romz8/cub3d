/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:05:49 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/19 17:05:53 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
receive a path as input, frame and integer
will open the file in the path, if negative will set to zero the array which 
index value correspond to the integer in input, display error message and 
return -1. 
otherwise close the opened path and set this very index to 1. it allows
to check a specific texture assets and return 0 or 1 to know if file can be
opened
*/
int	check_path(char *path, t_frame *frame, int i)
{
	int		fd;
	char	*card[4];

	card[NORTH] = "NORTH";
	card[SOUTH] = "SOUTH";
	card[WEST] = "WEST";
	card[EAST] = "EAST";
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		frame->load_scss[i] = 0;
		printf("Error impossible to load wall %s, replace with color 0x%x\n" \
		, card[i], frame->bckup_clr[i]);
		return (-1);
	}
	close(fd);
	frame->load_scss[i] = 1;
	return (0);
}

/*
iterate over texture loaded into map object and, if the load_success is 1
(meaning the path could be opened) we load the texture to an image in the 
corresponding index of the loaded_texture array. If there is any issue
we setup the laod_success to 0. 
*/
void	texture_upload(t_frame *frame, t_map *map)
{
	t_img	img;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (frame->load_scss[i] == 1)
		{
			img = frame->loaded_texture[i];
			img.img = mlx_xpm_file_to_image(frame->mlx, map->texture[i], \
			&img.img_w, &img.img_h);
			img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
			&img.line_len, &img.endian);
			if (!img.addr || !img.img_w || !img.img_h)
				frame->load_scss[i] = 0;
			else
			{
				frame->loaded_texture[i] = img;
				frame->load_scss[i] = 1;
			}
		}
		i++;
	}
}

/*
loading a set of colours to paint the walls with if texture assets
encountered issue
*/
void	load_bckup_wall(t_frame *frame)
{
	frame->bckup_clr[0] = 0x00FF0000;
	frame->bckup_clr[1] = 0x0000FF00;
	frame->bckup_clr[2] = 0x000000FF;
	frame->bckup_clr[3] = 0x00FF00FF;
}

void	load_texture(t_frame *frame, t_map *map)
{
	int	i;

	load_bckup_wall(frame);
	i = 0;
	while (i < 4)
	{
		check_path(map->texture[i], frame, i);
		i++;
	}
	texture_upload(frame, map);
}

/* load sprite from assets*/
void	load_sprite(t_frame *frame)
{
	t_img	*img;
	char	*path[5];
	int		i;

	path[0] = "./assets/sprite/w3dfps1.xpm";
	path[1] = "./assets/sprite/w3dfps2.xpm";
	path[2] = "./assets/sprite/w3dfps2.xpm";
	path[3] = "./assets/sprite/w3dfps2.xpm";
	path[4] = "./assets/sprite/w3dfps2.xpm";
	i = 0;
	while (i < 5)
	{
		img = &frame->sprite[i];
		img->img = mlx_xpm_file_to_image(frame->mlx, path[i], &img->img_w, \
		&img->img_h);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_len, &img->endian);
		if (!img->addr)
		{
			printf("Asset sprite not loaded\n");
			exit(EXIT_FAILURE); // to replace with error management
		}
		frame->sprite[i] = *img;
		i++;
	}
}
