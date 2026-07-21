/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/21 18:51:23 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Error out unless only spaces/tabs remain from index i onward. */
static void	check_line_end(t_game *g, char *line, int i)
{
	skip_spaces(line, &i);
	if (line[i] != '\0')
		error_exit(g, "unexpected characters in element line");
}

/* Store the single token starting at pos as texture idx (must be unset). */
static void	set_texture(t_game *g, int idx, char *line, int pos)
{
	int		end;
	char	saved;

	skip_spaces(line, &pos);
	end = pos;
	while (line[end] && line[end] != ' ' && line[end] != '\t')
		end++;
	if (pos == end || g->tex_path[idx])
		error_exit(g, "missing or duplicate texture path");
	check_line_end(g, line, end);
	saved = line[end];
	line[end] = '\0';
	g->tex_path[idx] = str_dup(g, line + pos);
	line[end] = saved;
}

/* Parse one 0-255 byte at *i; advances past surrounding spaces. */
static int	parse_byte(t_game *g, char *line, int *i)
{
	int	val;
	int	digits;

	skip_spaces(line, i);
	val = 0;
	digits = 0;
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		val = val * 10 + (line[*i] - '0');
		digits++;
		(*i)++;
	}
	skip_spaces(line, i);
	if (digits == 0 || val > 255)
		error_exit(g, "invalid color component");
	return (val);
}

/* Parse "R,G,B" from pos and store it as floor (is_ceil 0) or ceiling. */
static void	parse_color(t_game *g, char *line, int pos, int is_ceil)
{
	int	rgb[3];
	int	k;

	k = 0;
	while (k < 3)
	{
		rgb[k] = parse_byte(g, line, &pos);
		if (k < 2 && line[pos++] != ',')
			error_exit(g, "invalid color format");
		k++;
	}
	if (line[pos] != '\0')
		error_exit(g, "invalid color format");
	if (is_ceil && !g->ceil_set)
	{
		g->ceil_color = rgba(rgb[0], rgb[1], rgb[2], 255);
		g->ceil_set = 1;
	}
	else if (!is_ceil && !g->floor_set)
	{
		g->floor_color = rgba(rgb[0], rgb[1], rgb[2], 255);
		g->floor_set = 1;
	}
	else
		error_exit(g, "duplicate floor or ceiling color");
}

/* Dispatch one config line to the matching texture or color parser. */
void	parse_config(t_game *g, char *line)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	if (line[i] == 'N' && line[i + 1] == 'O')
		set_texture(g, TEX_NO, line, i + 2);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		set_texture(g, TEX_SO, line, i + 2);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		set_texture(g, TEX_WE, line, i + 2);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		set_texture(g, TEX_EA, line, i + 2);
	else if (line[i] == 'F')
		parse_color(g, line, i + 1, 0);
	else
		parse_color(g, line, i + 1, 1);
}
