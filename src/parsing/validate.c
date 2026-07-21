/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/21 18:51:50 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Record the spawn cell centre and orientation, then blank the tile. */
static void	set_spawn(t_game *g, int x, int y, char c)
{
	g->player.x = x + 0.5;
	g->player.y = y + 0.5;
	set_player_dir(g, c);
	g->map[y][x] = '0';
}

/* Check one cell: returns 1 for a player start, 0 otherwise; errors on junk. */
static int	handle_cell(t_game *g, int x, int y)
{
	char	c;

	c = g->map[y][x];
	if (c == ' ' || c == '0' || c == '1')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		set_spawn(g, x, y, c);
		return (1);
	}
	error_exit(g, "invalid character in map");
	return (0);
}

/* Validate every cell and require exactly one player start position. */
static void	check_chars(t_game *g)
{
	int	x;
	int	y;
	int	players;

	players = 0;
	y = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_w)
		{
			players += handle_cell(g, x, y);
			x++;
		}
		y++;
	}
	if (players != 1)
		error_exit(g, "map must contain exactly one player start");
}

/* Flood the reachable floor; flag *open if it escapes into void/border. */
static void	flood(t_game *g, int x, int y, int *open)
{
	if (x < 0 || y < 0 || x >= g->map_w || y >= g->map_h)
	{
		*open = 1;
		return ;
	}
	if (g->map[y][x] == ' ')
	{
		*open = 1;
		return ;
	}
	if (g->map[y][x] == '1' || g->map[y][x] == 'F')
		return ;
	g->map[y][x] = 'F';
	flood(g, x + 1, y, open);
	flood(g, x - 1, y, open);
	flood(g, x, y + 1, open);
	flood(g, x, y - 1, open);
}

/* Restore flood markers, then run char + closure checks on the map. */
void	validate_map(t_game *g)
{
	int	open;
	int	x;
	int	y;

	check_chars(g);
	open = 0;
	flood(g, (int)g->player.x, (int)g->player.y, &open);
	y = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_w)
		{
			if (g->map[y][x] == 'F')
				g->map[y][x] = '0';
			x++;
		}
		y++;
	}
	if (open)
		error_exit(g, "the map is not closed by walls");
}
