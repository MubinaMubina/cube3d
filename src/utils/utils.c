/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/21 18:50:34 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint32_t	rgba(int r, int g, int b, int a)
{
	return ((uint32_t)r << 24 | (uint32_t)g << 16 | (uint32_t)b << 8 | a);
}

int	is_wall(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_w || y >= game->map_h)
		return (1);
	if (game->map[y][x] == '1' || game->map[y][x] == ' ')
		return (1);
	return (0);
}

size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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
