/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/16 00:00:00 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Pack 8-bit channels into MLX42's 0xRRGGBBAA format. */
uint32_t	rgba(int r, int g, int b, int a)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | a);
}

/* A cell is solid if out of bounds, a wall '1', or map void (space). */
int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_w || y >= game->map_h)
		return (1);
	if (game->map[y][x] == '1' || game->map[y][x] == ' ')
		return (1);
	return (0);
}

/* Length of a NUL-terminated string. */
size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/* Duplicate a string on the heap; abort cleanly on allocation failure. */
char	*str_dup(t_game *game, const char *s)
{
	char	*copy;
	size_t	i;

	copy = malloc(str_len(s) + 1);
	if (!copy)
		error_exit(game, "allocation failed");
	i = 0;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
