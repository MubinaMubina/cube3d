/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::    */
/*   utils.c                                            :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+      */
/*   By: mmubina                                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/16                               #+#    #+#              */
/*   Updated: 2026/07/16                              ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Pack 8-bit channels into MLX42's 0xRRGGBBAA format. */
uint32_t	rgba(int r, int g, int b, int a)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | a);
}

/* Return 1 if the cell at (x, y) is a wall or out of bounds. */
int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_w || y >= game->map_h)
		return (1);
	return (game->map[y][x] == WALL);
}

/* Print an error, tear down MLX if it exists, and exit. */
void	error_exit(t_game *game, const char *msg)
{
	printf("Error\n%s\n", msg);
	if (game && game->mlx)
		mlx_terminate(game->mlx);
	exit(EXIT_FAILURE);
}
