/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:57:49 by frmurcia          #+#    #+#             */
/*   Updated: 2023/12/13 19:37:34 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// *texture->info[] es la particion en lineas de texture_raw
void process_texture_raw(t_textures *texture)
{
   	int		i;
	char	*info;
	char	**paths;
   
	i = 0;
	texture->info = ft_split(texture->texture_raw, '\n');//texture->info[] es cada linea
    while (i < 6 && texture->info[i])
    {
		texture->type = get_texture_type(texture, i);
		paths = ft_split(texture->info[i], ' ');
		info = ft_strtrim(paths[1], " ");
		if (texture->type == NO)
			texture->paths->north = info;
		else if (texture->type == SO)
			texture->paths->south = info;
		else if (texture->type == WE)
			texture->paths->west = info;
		else if (texture->type == EA)
			texture->paths->east = info;
		else if (texture->type == F)
			texture->paths->floor = info;
		else if (texture->type == C)
			texture->paths->ceil = info;
        i++;
    }
}

bool	only_map_chars(char *line)
{
	bool	found_map;
	size_t	i;
	size_t	length;

	found_map = false;
	i = 0;
	length = ft_strlen(line);
	while (i < ft_strlen(line))
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			found_map = true;
			i++;
		}
		else if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		else
			return (false);
	}
	return (found_map);
}

void	process_textures(t_textures *texture, char *line)
{
	if (!texture->texture_raw && !only_map_chars(line))
		texture->texture_raw = ft_strdup(line);
	else if (texture->texture_raw && !only_map_chars(line))
		texture->texture_raw = ft_strjoin(texture->texture_raw, line);
	free(line);
}

void	ft_read_textures(char **argv, t_textures *texture)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_write_error("Error opening map file\n");
	line = get_next_line(fd);
	if (!line)
		ft_write_error("Error reading lines of the map\n");
	texture->texture_raw = NULL;
	while (line)
	{
		if (!is_empty_or_spaces(line))
			process_textures(texture, line);
		line = get_next_line(fd);
		if (!line)
			break ;
	}
	free(line);
}
