/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:59:53 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 15:57:59 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t	*load_single_image(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (g_eno = E_ALLOC, ft_error(), NULL);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

static t_images	load_images(mlx_t *mlx)
{
	t_images	images;

	images.bloc0 = load_single_image(mlx, "assets/texture0.png");
	images.bloc1 = load_single_image(mlx, "assets/texture1.png");
	images.blocP = load_single_image(mlx, "assets/textureP.png");
	images.blocE = load_single_image(mlx, "assets/textureE.png");
	images.blocC = load_single_image(mlx, "assets/textureC.png");
	return (images);
}

static mlx_image_t	*get_image_by_tile(t_images *images, char tile)
{
	if (tile == '0')
		return (images->bloc0);
	if (tile == '1')
		return (images->bloc1);
	if (tile == 'E')
		return (images->blocE);
	if (tile == 'P')
		return (images->blocP);
	if (tile == 'C')
		return (images->blocC);
	return (NULL);
}

static void	draw_tile(mlx_t *mlx, t_map map, t_images images, t_pos pos)
{
	mlx_image_t	*image;
	size_t		z_img;

	z_img = 0;
	image = get_image_by_tile(&images, '0');
	if (mlx_image_to_window(mlx, image, pos.x * 32, pos.y * 32) == -1)
		return (g_eno = E_ALLOC, ft_error());
	image->instances[image->count - 1].z = z_img;
	if (map.tiles[pos.y][pos.x] == 'E' \
		|| map.tiles[pos.y][pos.x] == 'C' \
		|| map.tiles[pos.y][pos.x] == '1')
		z_img = 1;
	if (map.tiles[pos.y][pos.x] == 'P')
		z_img = 2;
	image = get_image_by_tile(&images, map.tiles[pos.y][pos.x]);
	mlx_image_to_window(mlx, image, pos.x * 32, pos.y * 32);
	image->instances[image->count - 1].z = z_img;
}

t_images	images_to_window(mlx_t *mlx, t_map map)
{
	t_images	images;
	t_pos		pos;

	images = load_images(mlx);
	pos.y = 0;
	while (pos.y < map.height)
	{
		pos.x = 0;
		while (pos.x < map.width)
		{
			draw_tile(mlx, map, images, pos);
			pos.x++;
		}
		pos.y++;
	}
	return (images);
}
