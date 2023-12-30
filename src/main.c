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

void	print_showoff(void)
{
	ft_putstr_fd("   ____   _      _   ___    ___ \n", STDOUT_FILENO);
	ft_putstr_fd(" / ___| | |    | | |___) ) |___\n", STDOUT_FILENO);
	ft_putstr_fd("| |     | |    | |  ___     __|\n", STDOUT_FILENO);
	ft_putstr_fd("| |___  | | _ _| | | ___)  |____ \n", STDOUT_FILENO);
	ft_putstr_fd(" \\____/ |__ __ __| ____________| \n", STDOUT_FILENO);
	ft_putstr_fd("\nControls:\n", STDOUT_FILENO);
	ft_putstr_fd("WASD + Up/Down: Move\n", STDOUT_FILENO);
	ft_putstr_fd("Left/Right Arrows or Mouse: Rotate\n", STDOUT_FILENO);
	ft_putstr_fd("Left Click: Fire your gun\n", STDOUT_FILENO);
	ft_putstr_fd("Press 'ESC' to quit\n", STDOUT_FILENO);
}

void	build_game(t_frame *frame, t_img *img, t_player *player, t_map *map)
{
	frame->mlx = mlx_init();
	frame->mlx_wdw = mlx_new_window(frame->mlx, WIDTH, LENGTH, "Cub3D");
	img->img = mlx_new_image(frame->mlx, WIDTH, LENGTH);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_len, &img->endian);
	frame->img = *img;
	init_player(frame, player, map);
	frame->player = *player;
	frame->game_map = map->map_2d;
	frame->map_w = map->max_width;
	frame->map_h = map->max_height;
	frame->floor_color = create_hex_trgb(0, map->color_f[0], \
	map->color_f[1], map->color_f[2]);
	frame->ceiling_color = create_hex_trgb(0, map->color_c[0], \
	map->color_c[1], map->color_c[2]);
}

int	main(int argc, char **argv)
{
	t_frame		frame;
	t_img		img;
	t_player	player;
	t_map		map;

	ft_check_parameters(argc, argv);
	map = ft_start_map(argv);
	print_showoff();
	build_game(&frame, &img, &player, &map);
	load_texture(&frame, &map);
	free_loader(&map);
	load_sprite(&frame);
	mlx_mouse_move(frame.mlx_wdw, WIDTH / 2, LENGTH / 2);
	mlx_hook(frame.mlx_wdw, 2, 1L << 0, key_hook_press, &frame);
	mlx_hook(frame.mlx_wdw, 3, 1L << 0, key_hook_release, &frame);
	mlx_hook(frame.mlx_wdw, 17, 0, close_handler, &frame);
	mlx_mouse_hook(frame.mlx_wdw, sprite_hook, &frame);
	mlx_loop_hook(frame.mlx, render, &frame);
	mlx_loop(frame.mlx);
}
