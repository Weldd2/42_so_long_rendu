/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_closed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 18:06:03 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 18:17:57 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_ok	is_closed(t_map map)
{
	size_t	index;

	index = 0;
	while (index < map.width)
	{
		if (map.tiles[0][index] != '1')
			return (E_ERR);
		if (map.tiles[map.height - 1][index] != '1')
			return (E_ERR);
		index++;
	}
	index = 0;
	while (index < map.height)
	{
		if (map.tiles[index][map.width - 1] != '1')
			return (E_ERR);
		if (map.tiles[index][0] != '1')
			return (E_ERR);
		index++;
	}
	return (E_OK);
}
