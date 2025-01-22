/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:29:02 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 16:00:46 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	**init_visited(size_t height, size_t width)
{
	bool	**visited;
	size_t	y;
	size_t	x;

	visited = mem_malloc(sizeof(bool *) * height);
	if (!visited)
		return (g_eno = E_ALLOC, ft_error(), NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		visited[y] = mem_malloc(sizeof(bool) * width);
		if (!visited[y])
			return (g_eno = E_ALLOC, ft_error(), NULL);
		while (x < width)
		{
			visited[y][x] = false;
			x++;
		}
		y++;
	}
	return (visited);
}

void	free_visited(bool **visited, size_t height)
{
	size_t	index;

	index = 0;
	if (!visited)
		return ;
	while (index < height)
	{
		mem_free(visited[index]);
		index++;
	}
	mem_free(visited);
}

void	enqueue_tiles(t_map *map, t_queue *queue, t_pos current, bool **visited)
{
	size_t	x;
	size_t	y;

	x = current.x;
	y = current.y;
	if (map->tiles[y + 1][x] != '1' && !visited[y + 1][x])
	{
		enqueue(queue, (t_pos){.y = y + 1, .x = x});
		visited[y + 1][x] = true;
	}
	if (map->tiles[y - 1][x] != '1' && !visited[y - 1][x])
	{
		enqueue(queue, (t_pos){.y = y - 1, .x = x});
		visited[y - 1][x] = true;
	}
	if (map->tiles[y][x + 1] != '1' && !visited[y][x + 1])
	{
		enqueue(queue, (t_pos){.y = y, .x = x + 1});
		visited[y][x + 1] = true;
	}
	if (map->tiles[y][x - 1] != '1' && !visited[y][x - 1])
	{
		enqueue(queue, (t_pos){.y = y, .x = x - 1});
		visited[y][x - 1] = true;
	}
}

t_ok	bfs(t_map *map, size_t start_y, size_t start_x)
{
	bool	**visited;
	t_queue	*q;
	size_t	collected;
	t_pos	current;
	bool	is_e_accesible;

	visited = init_visited(map->height, map->width);
	q = init_queue(map->height * map->width);
	enqueue(q, (t_pos){.x = start_x, .y = start_y});
	visited[start_y][start_x] = true;
	collected = 0;
	is_e_accesible = false;
	while (!is_empty(q))
	{
		current = dequeue(q);
		if (map->tiles[current.y][current.x] == 'C')
			collected++;
		if (map->tiles[current.y][current.x] == 'E')
			is_e_accesible = true;
		if (is_e_accesible && collected == map->c_count)
			return (free_visited(visited, map->height), free_queue(q), E_OK);
		enqueue_tiles(map, q, current, visited);
	}
	return (free_visited(visited, map->height), free_queue(q), E_ERR);
}
