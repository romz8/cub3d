/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:35:55 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/08 11:36:09 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_img_add(void *img);

char	*load_texture(t_frame *frame, char *path)
{
	void	*img;
	char	*img_addr;
	int		img_w;
	int		img_h;
	char	*texture;
	int		bitmapsize;
	int		x;
	int		y;

	img = mlx_xpm_file_to_image(frame->mlx, path, &img_w, &img_h);
	img_addr = get_img_add(img);
	bitmapsize = bitmap * bitmap * 4;
	texture = ft_calloc(bitmapsize, sizeof(char));
	x = 0;
	while (x < bitmap)
	{
		y = 0;
		while (y < bitmap)
		{
			int destx = (x * img_w) / 64;
			int desty = (y * img_h) / 64;
			int newIndex = (y * 64 + x) * 4;
        	int origIndex = (desty * img_w + destx) * 4;
        	ft_memcpy(&texture[newIndex], &img_addr[origIndex], 4);
		}
	}
	return (texture);
}

void	wall_to_texture(t_frame *frame, t_ray *ray)
{
	double wallx;
	int		textx;
	if (ray->side == 0)
		wallx = frame->player.py + ray->wall_dist * ray->ray_diry;
	else
		wallx = frame->player.px+ ray->wall_dist * ray->ray_dirx;
	wallx -= floor(wallx);
	textx = (int) (wallx * (double) bitmap);
	if (ray->side == 0 && ray->ray_dirx > 0)
		textx = bitmap - textx;
	if (ray->side == 1 && ray->ray_dirx < 0)
		textx = bitmap - textx;

}

char	*get_img_add(void *img)
{
	int		bits_per_pixel; 
	int		size_line;
	int 	endian;
	char	*addr;

	addr = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
	return (addr);

}