/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/16 00:00:00 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Set the direction and camera-plane vectors from the spawn character. */
void	set_player_dir(t_game *game, char c)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	if (c == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = FOV;
	}
	else if (c == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = -FOV;
	}
	else if (c == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = FOV;
	}
	else if (c == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = -FOV;
	}
}

/* Create the window and drawing image, then load the wall textures. */
void	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WIN_W, WIN_H, "cub3D", false);
	if (!game->mlx)
		error_exit(game, "mlx_init failed");
	game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->img || mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_exit(game, "image creation failed");
	load_textures(game);
}
