/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::    */
/*   render.c                                           :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+      */
/*   By: mmubina                                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/16                               #+#    #+#              */
/*   Updated: 2026/07/16                              ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Flat colour per wall face; textures replace this in a later milestone. */
static uint32_t	wall_color(t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->step_y > 0)
			return (rgba(160, 40, 40, 255));
		return (rgba(40, 40, 160, 255));
	}
	if (ray->step_x > 0)
		return (rgba(40, 160, 40, 255));
	return (rgba(200, 200, 60, 255));
}

/* Draw one screen column: ceiling, wall stripe, floor. */
void	put_vertical(t_game *game, int x, t_ray *ray)
{
	int			y;
	uint32_t	color;

	color = wall_color(ray);
	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, game->ceil_color);
	while (y <= ray->draw_end)
		mlx_put_pixel(game->img, x, y++, color);
	while (y < WIN_H)
		mlx_put_pixel(game->img, x, y++, game->floor_color);
}

/* Called every frame by mlx_loop_hook: move, then redraw all columns. */
void	render_frame(void *param)
{
	t_game	*game;
	t_ray	ray;
	int		x;

	game = (t_game *)param;
	move_player(game);
	x = 0;
	while (x < WIN_W)
	{
		cast_ray(game, &ray, x);
		put_vertical(game, x, &ray);
		x++;
	}
}
