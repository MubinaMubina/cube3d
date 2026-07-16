/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::    */
/*   main.c                                             :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+      */
/*   By: mmubina                                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/16                               #+#    #+#              */
/*   Updated: 2026/07/16                              ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(t_game *game)
{
	int	y;

	if (!game->map)
		return ;
	y = 0;
	while (y < game->map_h)
		free(game->map[y++]);
	free(game->map);
	game->map = NULL;
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	init_game(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game);
	return (EXIT_SUCCESS);
}
