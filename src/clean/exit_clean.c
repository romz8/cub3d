/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:37:58 by rjobert           #+#    #+#             */
/*   Updated: 2023/12/30 16:38:00 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void  free_map(t_frame *frame)
{
  int	i;

  if (!frame)
	return ;
  if (frame->game_map)
  {
    i = 0;
	while (i < frame->map_h)
    {
      if (frame->game_map[i])
        free(frame->game_map[i]);
      i++;
    }
    free(frame->game_map);
  }
}

void free_loader(t_map	*map)
{
	int	i;
	if (!map)
		return ;
	i = 0;
	while (i < 4)
	{
		if (map->texture[i])
			free(map->texture[i]);
		i++;
	}
}
void	free_textures(t_textures *texture)
{
	int	i;

	i = 0;
	if (texture)
	{
		if (texture->path != NULL)
			free(texture->path);
		if (texture->texture_raw)
			free(texture->texture_raw);
		if (texture->paths->floor)
			free(texture->paths->floor);
		if (texture->paths->ceil)
			free(texture->paths->ceil);
		if (texture->paths)
			free(texture->paths);
	}
}

void	free_mapcolor(t_map_color *color)
{
	if (color->ceil_color)
		free(color->ceil_color);
	if (color->floor_color)
		free(color->floor_color);
}


