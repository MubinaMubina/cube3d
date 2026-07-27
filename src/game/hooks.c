/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/16 00:00:00 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

static void	try_move(t_game *game, double nx, double ny)
{
	if (!is_wall(game, (int)nx, (int)game->player.y))
		game->player.x = nx;
	if (!is_wall(game, (int)game->player.x, (int)ny))
		game->player.y = ny;
}

static void	rotate_view(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	move_player(t_game *game)
{
	t_player	*p;
	double		move;
	double		rot;

	p = &game->player;
	move = MOVE_SPEED * game->mlx->delta_time;
	rot = ROT_SPEED * game->mlx->delta_time;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		try_move(game, p->x + p->dir_x * move, p->y + p->dir_y * move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		try_move(game, p->x - p->dir_x * move, p->y - p->dir_y * move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		try_move(game, p->x - p->dir_y * move, p->y + p->dir_x * move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		try_move(game, p->x + p->dir_y * move, p->y - p->dir_x * move);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_view(p, -rot);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_view(p, rot);
}
