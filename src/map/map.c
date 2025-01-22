/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:48:57 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 16:44:32 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*gnl_and_trim(int fd)
{
	char	*line;
	char	*trimmed_line;

	line = gnl_get_next_line(fd);
	if (line == NULL)
		return (NULL);
	trimmed_line = str_strtrim(line, "\n ");
	mem_free(line);
	return (trimmed_line);
}

static int	init_map_tiles(int fd, t_map *map)
{
	char	*line;
	size_t	index;

	index = 0;
	map->tiles = NULL;
	while (true)
	{
		line = gnl_and_trim(fd);
		if (line == NULL)
			break ;
		if (line[0] == '\0')
		{
			mem_free(line);
			continue ;
		}
		map->tiles = mem_realloc(map->tiles, (index + 1) * sizeof(char *));
		map->tiles[index] = line;
		mem_mgc_add_block(map->tiles[index], mem_free);
		index++;
	}
	if (map->tiles != NULL)
		mem_mgc_add_block(map->tiles, mem_free);
	return (index);
}

void	init_map(int fd, t_map *map)
{
	size_t	index;

	index = init_map_tiles(fd, map);
	if (index == 0)
		return (g_eno = E_MAPEMPTY, ft_error());
	map->height = index;
	map->width = str_strlen(map->tiles[0]);
	map->p_x = 0;
	map->p_y = 0;
	map->c_count = 0;
	map->p_count = 0;
	map->e_count = 0;
}
