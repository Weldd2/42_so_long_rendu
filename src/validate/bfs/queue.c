/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:27:26 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/21 15:59:44 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_empty(t_queue *queue)
{
	if (!queue)
		return (false);
	return (queue->front == queue->rear);
}

bool	enqueue(t_queue *queue, t_pos pos)
{
	if (!queue)
		return (false);
	queue->data[queue->rear] = pos;
	queue->rear++;
	return (true);
}

t_pos	dequeue(t_queue *queue)
{
	t_pos	out;

	if (!queue || is_empty(queue))
		return ((t_pos){.x = 0, .y = 0});
	out = queue->data[queue->front];
	queue->front++;
	return (out);
}

t_queue	*init_queue(size_t capacity)
{
	t_queue	*queue;

	queue = mem_malloc(sizeof(t_queue));
	if (!queue)
		return (g_eno = E_ALLOC, ft_error(), NULL);
	queue->capacity = capacity;
	queue->data = mem_malloc(capacity * sizeof(t_pos));
	if (!queue->data)
		return (g_eno = E_ALLOC, ft_error(), NULL);
	queue->front = 0;
	queue->rear = 0;
	return (queue);
}

void	free_queue(t_queue *queue)
{
	if (!queue)
		return ;
	mem_free(queue->data);
	mem_free(queue);
}
