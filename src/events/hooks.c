/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:43:52 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/06 11:43:54 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
int key_hook(int keycode, t_frame *frame)
{
	if (keycode == 53)
		esc_hook(keycode, frame);
	else
		move(keycode, frame);
	return (0);
}

int mouse_event(t_frame *frame)
{
	int	x;
	int	y;
	int	movement;
	
	mlx_mouse_get_pos(frame->mlx_wdw, &x, &y);
	printf("mouse coordinate at by (x,y) = %i, %i \n", x, y);
	
	if (x < 0 || y < 0 || x > WIDTH || y > LENGTH)
		return (0);
	else
		movement = (WIDTH / 2 ) - x;
	if (movement < 200)
		rotate_vector(frame, 0.05);
	else if (movement > 200)
		rotate_vector(frame, 0.05);
	draw_player(frame);
	return (1);
}