/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::    */
/*   init.c                                             :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+      */
/*   By: mmubina                                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/16                               #+#    #+#              */
/*   Updated: 2026/07/16                              ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Hardcoded map for this milestone; parsing replaces it later. */
static const int	g_demo_map[8][12] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

/* Copy the demo map into a heap grid so it matches the parsed layout. */
static void	load_demo_map(t_game *game)
{
	int	x;
	int	y;

	game->map_w = 12;
	game->map_h = 8;
	game->map = malloc(sizeof(int *) * game->map_h);
	if (!game->map)
		error_exit(game, "map allocation failed");
	y = 0;
	while (y < game->map_h)
	{
		game->map[y] = malloc(sizeof(int) * game->map_w);
		if (!game->map[y])
			error_exit(game, "map allocation failed");
		x = 0;
		while (x < game->map_w)
		{
			game->map[y][x] = g_demo_map[y][x];
			x++;
		}
		y++;
	}
}

/* Player starts looking north (dir 0,-1); plane is perpendicular for FOV. */
static void	init_player(t_game *game)
{
	game->player.x = 2.5;
	game->player.y = 5.5;
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = FOV;
	game->player.plane_y = 0;
}

void	init_game(t_game *game)
{
	memset(game, 0, sizeof(t_game));
	game->ceil_color = CEIL_COLOR;
	game->floor_color = FLOOR_COLOR;
	load_demo_map(game);
	init_player(game);
	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
	if (!game->mlx)
		error_exit(game, "mlx_init failed");
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_exit(game, "image creation failed");
}
