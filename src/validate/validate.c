/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:57:50 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/14 17:35:31 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_ok	validate(t_map *map)
{
	if (is_rectangular(*map) != E_OK)
		return (g_eno = E_MAPWIDTH, E_ERR);
	if (is_closed(*map) != E_OK)
		return (g_eno = E_MAPEDGES, E_ERR);
	if (is_playable(map) != E_OK)
		return (E_ERR);
	if (is_finishable(map) != E_OK)
		return (g_eno = E_FINISHABLE, E_ERR);
	return (E_OK);
}
