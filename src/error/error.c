/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:00:52 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 16:57:41 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_errno	g_eno;

static void	printerr(void)
{
	static const char	*errstr[] = {\
		[E_GLOBAL] = "An error occured", \
		[E_ALLOC] = "Allocation Failed", \
		[E_FILENAME] = "File name must finish with .ber", \
		[E_OPEN] = "Could not open file.", \
		[E_ARGS] = "1 argument expected.", \
		[E_MAPEMPTY] = "Map is empty", \
		[E_MAPWIDTH] = "Map has lines of different width.", \
		[E_MAPEDGES] = "Map is not surrounded by walls.", \
		[E_FINISHABLE] = "Map is not finishable.", \
		[E_INVALID_CHAR] = "Invalid char found.", \
		[E_COLLECTIBLE] = "Less than one collectible found", \
		[E_EXIT] = "Map must have exactly one exit", \
		[E_PLAYER] = "Map must have exactly one player", \
		[E_NO_ERROR] = "", \
	};

	if (errstr[g_eno])
		pf_printf("Error\n%s\n", errstr[g_eno]);
}

void	ft_error(void)
{
	printerr();
	mem_mgc_free();
	exit(EXIT_FAILURE);
}
