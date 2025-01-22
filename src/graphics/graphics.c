/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:58:20 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 16:51:21 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	graph(t_map map)
{
	mlx_t		*mlx;
	t_images	images;

	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(map.width * 32, map.height * 32, "IL EST PAS BO ?", true);
	if (!mlx)
		return (g_eno = E_ALLOC, ft_error());
	mem_mgc_add_block((void *)mlx, (void *)(void *)mlx_terminate);
	if (!mlx)
		ft_error();
	images = images_to_window(mlx, map);
	mlx_key_hook(mlx, &direction_keyhook, &(t_game){
		.map = &map,
		.mlx = mlx,
		.images = &images
	});
	mlx_loop(mlx);
}
