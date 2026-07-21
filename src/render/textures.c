/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/16 00:00:00 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Load the four wall textures from their parsed PNG paths. */
void	load_textures(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		g->tex[i] = mlx_load_png(g->tex_path[i]);
		if (!g->tex[i])
			error_exit(g, "failed to load a texture PNG");
		i++;
	}
}

/* Pick the wall face texture and the texture column that the ray hit. */
void	compute_texture(t_game *game, t_ray *ray)
{
	mlx_texture_t	*tex;

	if (ray->side == 0)
	{
		ray->wall_x = game->player.y + ray->perp_dist * ray->dir_y;
		if (ray->dir_x > 0)
			ray->tex_num = TEX_WE;
		else
			ray->tex_num = TEX_EA;
	}
	else
	{
		ray->wall_x = game->player.x + ray->perp_dist * ray->dir_x;
		if (ray->dir_y > 0)
			ray->tex_num = TEX_NO;
		else
			ray->tex_num = TEX_SO;
	}
	ray->wall_x -= floor(ray->wall_x);
	tex = game->tex[ray->tex_num];
	ray->tex_x = (int)(ray->wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
}

/* Read the RGBA texel at (x, y) and pack it into 0xRRGGBBAA. */
uint32_t	sample_texture(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*p;
	int		idx;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= (int)tex->width)
		x = tex->width - 1;
	if (y >= (int)tex->height)
		y = tex->height - 1;
	idx = (y * (int)tex->width + x) * 4;
	p = tex->pixels + idx;
	return (rgba(p[0], p[1], p[2], p[3]));
}
