/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:36:11 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 16:58:06 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	if (argc != 2)
		return (g_eno = E_ARGS, ft_error(), E_ERR);
	if (str_strendwith(argv[1], ".ber") != 1)
		return (g_eno = E_FILENAME, ft_error(), E_ERR);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (g_eno = E_OPEN, ft_error(), E_ERR);
	init_map(fd, &map);
	if (validate(&map) == E_ERR)
		ft_error();
	graph(map);
	mem_mgc_free();
	return (EXIT_SUCCESS);
}
