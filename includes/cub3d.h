/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::    */
/*   cub3d.h                                            :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+      */
/*   By: mmubina                                    +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+            */
/*   Created: 2026/07/16                               #+#    #+#              */
/*   Updated: 2026/07/16                              ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

/* Window dimensions. */
# define WIN_W 1024
# define WIN_H 768

/* Movement / rotation speed (per frame, scaled by delta_time). */
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0

/* Field of view: the camera plane length. 0.66 ~= 66 degrees. */
# define FOV 0.66

/* Map cell types. */
# define EMPTY 0
# define WALL 1

/* Ceiling / floor colours (RGBA), used until parsing sets them. */
# define CEIL_COLOR 0x87CEEBFF
# define FLOOR_COLOR 0x707070FF

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* Per-ray state for one vertical stripe. */
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	int			**map;
	int			map_w;
	int			map_h;
	uint32_t	ceil_color;
	uint32_t	floor_color;
}	t_game;

/* init.c */
void		init_game(t_game *game);

/* render.c */
void		render_frame(void *param);
void		put_vertical(t_game *game, int x, t_ray *ray);

/* raycast.c */
void		cast_ray(t_game *game, t_ray *ray, int x);

/* hooks.c */
void		key_hook(mlx_key_data_t keydata, void *param);
void		move_player(t_game *game);

/* utils.c */
uint32_t	rgba(int r, int g, int b, int a);
void		error_exit(t_game *game, const char *msg);
int			is_wall(t_game *game, int x, int y);

#endif
