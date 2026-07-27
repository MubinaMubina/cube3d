/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/21 18:51:35 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	map_end(char **lines, int start)
{
	int	i;

	i = start;
	while (lines[i] && !line_is_empty(lines[i]))
		i++;
	return (i);
}

static void	check_map_last(t_game *g, char **lines, int end)
{
	while (lines[end])
	{
		if (!line_is_empty(lines[end]))
			error_exit(g, "the map must be the last element");
		end++;
	}
}

static int	max_width(char **lines, int start, int end)
{
	int	i;
	int	w;
	int	len;

	w = 0;
	i = start;
	while (i < end)
	{
		len = (int)str_len(lines[i]);
		if (len > w)
			w = len;
		i++;
	}
	return (w);
}

static void	copy_row(char *dst, char *src, int w)
{
	int	i;
	int	len;

	len = (int)str_len(src);
	i = 0;
	while (i < w)
	{
		if (i < len)
			dst[i] = src[i];
		else
			dst[i] = ' ';
		i++;
	}
	dst[w] = '\0';
}

void	build_map(t_game *g, char **lines, int start)
{
	int	end;
	int	y;

	end = map_end(lines, start);
	check_map_last(g, lines, end);
	g->map_h = end - start;
	if (g->map_h <= 0)
		error_exit(g, "the map is empty");
	g->map_w = max_width(lines, start, end);
	g->map = malloc(sizeof(char *) * (g->map_h + 1));
	if (!g->map)
		error_exit(g, "allocation failed");
	y = 0;
	while (y < g->map_h)
	{
		g->map[y] = malloc(g->map_w + 1);
		if (!g->map[y])
			error_exit(g, "allocation failed");
		copy_row(g->map[y], lines[start + y], g->map_w);
		y++;
	}
	g->map[g->map_h] = NULL;
}
