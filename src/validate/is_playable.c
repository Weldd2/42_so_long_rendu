/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_playable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:20:50 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 23:21:40 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_ok	handle_char(t_map *map, char c, size_t x, size_t y)
{
	if (c != '1' && c != 'E' && c != 'C' && c != 'P' && c != '0')
		return (E_ERR);
	if (c == 'E')
		map->e_count += 1;
	if (c == 'C')
		map->c_count += 1;
	if (c == 'P')
	{
		map->p_count += 1;
		map->p_x = x;
		map->p_y = y;
	}
	return (E_OK);
}

t_ok	is_playable(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (handle_char(map, map->tiles[y][x], x, y) == E_ERR)
				return (g_eno = E_INVALID_CHAR, E_ERR);
			x++;
		}
		y++;
	}
	if (map->c_count == 0)
		return (g_eno = E_COLLECTIBLE, E_ERR);
	if (map->e_count != 1)
		return (g_eno = E_EXIT, E_ERR);
	if (map->p_count != 1)
		return (g_eno = E_PLAYER, E_ERR);
	return (E_OK);
}
