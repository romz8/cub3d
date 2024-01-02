/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmurcia <frmurcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 12:57:49 by frmurcia          #+#    #+#             */
/*   Updated: 2024/01/02 10:24:46 by frmurcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_type(t_textures *texture, char *info, char **paths)
{
	if (ft_strcmp("NO", paths[0]) && texture->paths->north == NULL)
		texture->paths->north = ft_strdup(info);
	else if (ft_strcmp("SO", paths[0]) && texture->paths->south == NULL)
		texture->paths->south = ft_strdup(info);
	else if (ft_strcmp("WE", paths[0]) && texture->paths->west == NULL)
		texture->paths->west = ft_strdup(info);
	else if (ft_strcmp("EA", paths[0]) && texture->paths->east == NULL)
		texture->paths->east = ft_strdup(info);
	else if (ft_strcmp("F", paths[0]) && texture->paths->floor == NULL)
		texture->paths->floor = ft_strdup(info);
	else if (ft_strcmp("C", paths[0]) && texture->paths->ceil == NULL)
		texture->paths->ceil = ft_strdup(info);
	else
		ft_write_error("Error\nUnrecognized line in the file\n");
}

void	ft_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	process_texture_raw(t_textures *texture)
{
	int		i;
	char	**paths;
	char	**aux;
	char	*textinfo;

	i = -1;
	aux = ft_split(texture->texture_raw, '\n');
	while (aux[++i])
	{
		textinfo = free_spaces(aux[i]);
		paths = ft_split(textinfo, ' ');
		free(textinfo);
		if (paths[2] && paths[2] != NULL)
			ft_write_error("Error\nUnrecognized line\n");
		textinfo = ft_strtrim(paths[1], " ");
		get_texture_type(texture, textinfo, paths);
		free(textinfo);
		ft_free_paths(paths);
	}
	i = 0;
	while (aux[i])
		free(aux[i++]);
	free(aux);
	if (!are_texture_paths_filled(texture->paths))
		ft_write_error("Error\nTexture paths not filled\n");
}

bool	only_map_chars(char *line)
{
	bool	found_map;
	int		i;
	int		length;

	found_map = false;
	i = 0;
	length = ft_strlen(line);
	while (i < length)
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			found_map = true;
			i++;
		}
		else if (line[i] == ' ' || line[i] == '\n')
			i++;
		else
			return (false);
	}
	return (found_map);
}

void	process_textures(t_textures *texture, char *line)
{
	char	*tmp;

	texture->path_found = true;
	if (!texture->texture_raw)
		texture->texture_raw = ft_strdup(line);
	else if (texture->texture_raw)
	{
		tmp = ft_strjoin(texture->texture_raw, line);
		free(texture->texture_raw);
		texture->texture_raw = ft_strdup(tmp);
		free(tmp);
	}
}
