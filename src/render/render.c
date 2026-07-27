/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/21 18:50:19 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_wall(t_game *game, int x, t_ray *ray)
{
	mlx_texture_t	*tex;
	double			step;
	double			tex_pos;
	int				y;
	int				tex_y;

	tex = game->tex[ray->tex_num];
	step = (double)tex->height / ray->line_h;
	tex_pos = (ray->draw_start - WIN_H / 2.0 + ray->line_h / 2.0) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		mlx_put_pixel(game->img, x, y, sample_texture(tex, ray->tex_x, tex_y));
		y++;
	}
}

void	put_vertical(t_game *game, int x, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
		mlx_put_pixel(game->img, x, y++, game->ceil_color);
	draw_wall(game, x, ray);
	y = ray->draw_end + 1;
	while (y < WIN_H)
		mlx_put_pixel(game->img, x, y++, game->floor_color);
}

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
