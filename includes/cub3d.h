/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mk <mk@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/27 14:48:24 by mk               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>

/* Window dimensions. */
# define WIN_W 1024
# define WIN_H 768

/* Movement / rotation speed (per frame, scaled by delta_time). */
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0

/* Field of view: the camera plane length. 0.66 ~= 66 degrees. */
# define FOV 0.66

/* Texture indices: order of NO/SO/WE/EA in the tex arrays. */
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3

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
	double	wall_x;
	int		tex_num;
	int		tex_x;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	char			**map;
	int				map_w;
	int				map_h;
	uint32_t		ceil_color;
	uint32_t		floor_color;
	mlx_texture_t	*tex[4];
	char			*tex_path[4];
	int				floor_set;
	int				ceil_set;
}	t_game;

/* main.c */
void			error_exit(t_game *game, const char *msg);
void			cleanup(t_game *game);

/* init.c */
void			init_mlx(t_game *game);
void			set_player_dir(t_game *game, char c);

/* parse.c */
void			parse_scene(t_game *game, const char *path);
int				is_config_line(const char *line);
int				line_is_empty(const char *line);

/* parse_config.c */
void			parse_config(t_game *game, char *line);

/* parse_map.c */
void			build_map(t_game *game, char **lines, int start);

/* validate.c */
void			validate_map(t_game *game);

/* read_file.c */
char			**read_file(t_game *game, const char *path);

/* split_lines.c */
int				count_nl(const char *s);
void			fill_lines(t_game *game, char *content, char **lines);

/* render.c */
void			render_frame(void *param);
void			put_vertical(t_game *game, int x, t_ray *ray);

/* raycast.c */
void			cast_ray(t_game *game, t_ray *ray, int x);

/* textures.c */
void			load_textures(t_game *game);
void			compute_texture(t_game *game, t_ray *ray);
uint32_t		sample_texture(mlx_texture_t *tex, int x, int y);

/* hooks.c */
void			key_hook(mlx_key_data_t keydata, void *param);
void			move_player(t_game *game);

/* utils.c */
uint32_t		rgba(int r, int g, int b, int a);
int				is_wall(t_game *game, int x, int y);
size_t			str_len(const char *s);
char			*str_dup(t_game *game, const char *s);

/* utils2.c */
void			free_split(char **arr);
void			skip_spaces(const char *s, int *i);

#endif
