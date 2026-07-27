/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/21 18:51:01 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_zero(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->img = NULL;
	game->map = NULL;
	game->map_w = 0;
	game->map_h = 0;
	game->ceil_color = 0;
	game->floor_color = 0;
	game->floor_set = 0;
	game->ceil_set = 0;
	i = 0;
	while (i < 4)
	{
		game->tex[i] = NULL;
		game->tex_path[i] = NULL;
		i++;
	}
}

void	cleanup(t_game *game)
{
	int	i;

	if (game->map)
		free_split(game->map);
	i = 0;
	while (i < 4)
	{
		if (game->tex_path[i])
			free(game->tex_path[i]);
		if (game->tex[i])
			mlx_delete_texture(game->tex[i]);
		i++;
	}
	if (game->mlx)
		mlx_terminate(game->mlx);
}

void	error_exit(t_game *game, const char *msg)
{
	printf("Error\n%s\n", msg);
	cleanup(game);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_zero(&game);
	if (argc != 2)
		error_exit(&game, "usage: ./cub3D <scene.cub>");
	parse_scene(&game, argv[1]);
	init_mlx(&game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (EXIT_SUCCESS);
}
