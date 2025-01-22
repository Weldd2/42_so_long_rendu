/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amura <amura@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:07:55 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 16:11:15 by amura            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_ok	handle_collision(mlx_key_data_t keydata, t_map *map, mlx_t *mlx)
{
	if (keydata.key == MLX_KEY_W)
		return (map->tiles[map->p_y - 1][map->p_x] == '1');
	if (keydata.key == MLX_KEY_S)
		return (map->tiles[map->p_y + 1][map->p_x] == '1');
	if (keydata.key == MLX_KEY_A)
		return (map->tiles[map->p_y][map->p_x - 1] == '1');
	if (keydata.key == MLX_KEY_D)
		return (map->tiles[map->p_y][map->p_x + 1] == '1');
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
	return (E_ERR);
}

static void	handle_move(mlx_key_data_t keydata, t_map *map, t_images *images)
{
	if (keydata.key == MLX_KEY_W)
	{
		images->blocP->instances[0].y -= 32;
		map->p_y--;
	}
	if (keydata.key == MLX_KEY_S)
	{
		images->blocP->instances[0].y += 32;
		map->p_y++;
	}
	if (keydata.key == MLX_KEY_A)
	{
		images->blocP->instances[0].x -= 32;
		map->p_x--;
	}
	if (keydata.key == MLX_KEY_D)
	{
		images->blocP->instances[0].x += 32;
		map->p_x++;
	}
}

static void	handle_collect(t_map *map, t_images *images)
{
	size_t	i;

	i = 0;
	if (map->tiles[map->p_y][map->p_x] == 'C')
	{
		map->c_count--;
		while (i < images->blocC->count)
		{
			if ((size_t)images->blocC->instances[i].x == map->p_x * 32
				&& (size_t)images->blocC->instances[i].y == map->p_y * 32)
			{
				images->blocC->instances[i].z--;
				map->tiles[map->p_y][map->p_x] = '0';
			}
			i++;
		}
	}
}

static void	handle_escape(t_map *map, mlx_t *mlx)
{
	if (map->tiles[map->p_y][map->p_x] == 'E' && map->c_count == 0)
		mlx_close_window(mlx);
}

void	direction_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game			*game;
	static size_t	count = 0;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS
		&& handle_collision(keydata, game->map, game->mlx) == E_OK)
	{
		handle_move(keydata, game->map, game->images);
		handle_collect(game->map, game->images);
		count++;
		pf_printf("%d\n", count);
		handle_escape(game->map, game->mlx);
	}
}
