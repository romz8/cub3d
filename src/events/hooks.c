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
		free_map(frame);
		exit (0);
	}
	return (0);
}

int	close_handler(t_frame *frame)
{
	mlx_destroy_window(frame->mlx, frame->mlx_wdw);
	free_map(frame);
	exit (0);
}

/*
update the key struct inside the player struct. based
on mlx_hook function with press mask, we update to 1
when press -> this allow to keep moving as pressed
(see move.c)
*/
int	key_hook_press(int keycode, t_frame *frame)
{
	if (keycode == 53)
		esc_hook(keycode, frame);
	else if (keycode == ARROW_UP || keycode == W)
		frame->player.key.up = 1;
	else if (keycode == ARROW_DOWN || keycode == S)
		frame->player.key.down = 1;
	else if (keycode == A)
		frame->player.key.left = 1;
	else if (keycode == D)
		frame->player.key.right = 1;
	else if (keycode == ARROW_LEFT)
		frame->player.key.rotate_l = 1;
	else if (keycode == ARROW_RIGHT)
		frame->player.key.rotate_r = 1;
	return (0);
}

/*
update the key struct inside the player struct. based
on mlx_hook function with release mask, we update to 0
when key is released -> this allow to stop moving as pressed
(see move.c)
*/
int	key_hook_release(int keycode, t_frame *frame)
{
	if (keycode == ARROW_UP || keycode == W)
		frame->player.key.up = 0;
	else if (keycode == ARROW_DOWN || keycode == S)
		frame->player.key.down = 0;
	else if (keycode == A)
		frame->player.key.left = 0;
	else if (keycode == D)
		frame->player.key.right = 0;
	else if (keycode == ARROW_LEFT)
		frame->player.key.rotate_l = 0;
	else if (keycode == ARROW_RIGHT)
		frame->player.key.rotate_r = 0;
	return (0);
}

/*
moving the mouse with a gradual effect
we get the nouse position as per mlx lib function 
into int passed as ref x and y, if it is inside the screen
and not in the centre (x <> 200pxl) we then rotate the the
player vector by a certain radian angle, amplified by a ratio
of the distance to the centre to give a gradual effect
 */
int	mouse_event(t_frame *frame)
{
	int	x;
	int	y;
	int	movement;

	mlx_mouse_get_pos(frame->mlx_wdw, &x, &y);
	if (x < 0 || y < 0 || x > WIDTH || y > LENGTH)
		return (0);
	else
		movement = (WIDTH / 2) - x;
	if (movement > 200)
		rotate_vector(frame, -0.02 * (0.5 + (float) movement / WIDTH));
	else if (movement < -200)
		rotate_vector(frame, 0.02 * (0.5 + (float) -1.0 * movement / WIDTH));
	return (1);
}
