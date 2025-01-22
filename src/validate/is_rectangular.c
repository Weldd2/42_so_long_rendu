/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_rectangular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:17:33 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 17:13:13 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_ok	is_rectangular(t_map map)
{
	size_t	i;
	size_t	line_width;

	i = 0;
	while (i < map.height)
	{
		line_width = str_strlen(map.tiles[i]);
		if (line_width != map.width)
			return (E_ERR);
		i++;
	}
	return (E_OK);
}
