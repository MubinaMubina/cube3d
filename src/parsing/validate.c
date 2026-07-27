/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mk <mk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/27 15:51:46 by mk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	set_spawn(t_game *g, int x, int y, char c)
{
	g->player.x = x + 0.5;
	g->player.y = y + 0.5;
	set_player_dir(g, c);
	g->map[y][x] = '0';
}

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

/* Every floor component may be separate, but each one must be wall-enclosed. */
static void	check_closed(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_w)
		{
			if (g->map[y][x] == '0' && (x == 0 || y == 0
				|| x == g->map_w - 1 || y == g->map_h - 1))
				error_exit(g, "the map is not closed by walls");
			else if (g->map[y][x] == '0' && (g->map[y][x - 1] == ' '
				|| g->map[y][x + 1] == ' ' || g->map[y - 1][x] == ' '
				|| g->map[y + 1][x] == ' '))
				error_exit(g, "the map is not closed by walls");
			x++;
		}
		y++;
	}
}

/* Validate characters, player count, and closure of every floor component. */
void	validate_map(t_game *g)
{
	check_chars(g);
	check_closed(g);
}
