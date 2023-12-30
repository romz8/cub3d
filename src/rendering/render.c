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

void	draw_player(t_frame *frame, int i);

/*
render the game, first perform raycasting, then listen and execte mouse and 
move hooks - movement. push the image to window and then push min map
return 1 as per mlx_look_hoop requirements
*/
int	render(t_frame *frame)
{
	raycasting(frame);
	mouse_event(frame);
	move(frame);
	mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, frame->img.img, 0, 0);
	mini_map(frame); 
	draw_player(frame, 0);
	return (1);
}

/*
given a pxl coordinate (x, y), get the image address from mempory alignment
and change its colour by de-referencing to hex trgba scheme.
*/
void	fill_pxl_mlx(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH || y < 0 || y > LENGTH)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
	return ;
}

/*
draw the player sprite with a movement logic. input frame and int,
based on int render a specific image in the img of sprite array and 
render it (push it to the window frame) at designated pxl position
*/
void	draw_player(t_frame *frame, int i)
{
	int	adx;

	adx = 4;
	if (i == 0)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, \
		frame->sprite[i].img, WIDTH / 2 - 65, LENGTH - 175);
	if (i == 1)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, \
		frame->sprite[i].img, WIDTH / 2 - 65 + adx, LENGTH - 210);
	else if (i == 2)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, \
		frame->sprite[i].img, WIDTH / 2 - 65 + adx, LENGTH - 210);
	else if (i == 3)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, \
		frame->sprite[i].img, WIDTH / 2 - 65 + adx, LENGTH - 210);
	else if (i == 4)
		mlx_put_image_to_window(frame->mlx, frame->mlx_wdw, \
		frame->sprite[i].img, WIDTH / 2 - 65 + adx, LENGTH - 210);
}
