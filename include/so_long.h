/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:38:50 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 16:57:08 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42.h"
# include "gnl.h"
# include "pf_printf.h"
# include <stdbool.h>

typedef struct s_pos {
	size_t x;
	size_t y;
}	t_pos;

typedef struct s_queue {
	t_pos *data;
	size_t front;
	size_t rear;
	size_t capacity;
}	t_queue;

typedef struct	s_images
{
	mlx_image_t	*bloc0;
	mlx_image_t	*bloc1;
	mlx_image_t	*blocP;
	mlx_image_t	*blocC;
	mlx_image_t	*blocE;
}	t_images;

typedef struct s_map
{
	char		**tiles;
	size_t		width;
	size_t		height;
	size_t		c_count;
	size_t		e_count;
	size_t		p_count;
	size_t		p_x;
	size_t		p_y;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	mlx_t		*mlx;
	t_images	*images;
}	t_game;

typedef enum e_errno
{
	E_GLOBAL,
	E_ALLOC,
	E_OPEN,
	E_FILENAME,
	E_ARGS,
	E_MAPEMPTY,
	E_MAPWIDTH,
	E_MAPEDGES,
	E_FINISHABLE,
	E_INVALID_CHAR,
	E_COLLECTIBLE,
	E_EXIT,
	E_PLAYER,
	E_NO_ERROR,
}	t_errno;

extern t_errno	g_eno;

typedef enum e_ok
{
	E_OK = 0,
	E_ERR = 1
}	t_ok;

void			ft_error();
void			init_map(int fd, t_map *map);
t_ok			is_rectangular(t_map map);
t_ok			is_closed(t_map map);
t_ok			is_playable(t_map *map);
t_ok			is_finishable(t_map *map);
t_ok			validate(t_map *map);
void			free_assets(void);
void			graph(t_map map);
t_queue			*init_queue(size_t capacity);
void			free_queue(t_queue *queue);
bool			is_empty(t_queue *queue);
bool			enqueue(t_queue *queue, t_pos pos);
t_pos			dequeue(t_queue *queue);
bool			**init_visited(size_t height, size_t width);
void			free_visited(bool **visited, size_t height);
t_ok			bfs(t_map *map, size_t start_y, size_t start_x);
t_images		images_to_window(mlx_t *mlx, t_map map);
void			direction_keyhook(mlx_key_data_t keydata, void* param);

#endif
