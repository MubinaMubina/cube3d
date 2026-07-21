/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/16 00:00:00 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* True if the line contains only spaces/tabs (or is empty). */
int	line_is_empty(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

/* True if the identifier a/b is present at i and followed by a separator. */
static int	match_id(const char *line, int i, char a, char b)
{
	if (line[i] != a || line[i + 1] != b)
		return (0);
	if (line[i + 2] == ' ' || line[i + 2] == '\t' || line[i + 2] == '\0')
		return (1);
	return (0);
}

/* True if the line starts (after spaces) with a NO/SO/WE/EA/F/C element. */
int	is_config_line(const char *line)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	if (match_id(line, i, 'N', 'O') || match_id(line, i, 'S', 'O'))
		return (1);
	if (match_id(line, i, 'W', 'E') || match_id(line, i, 'E', 'A'))
		return (1);
	if ((line[i] == 'F' || line[i] == 'C')
		&& (line[i + 1] == ' ' || line[i + 1] == '\t'))
		return (1);
	return (0);
}

/* Validate the .cub extension and that all six elements were parsed. */
static void	check_scene(t_game *g, const char *path)
{
	size_t	len;

	len = str_len(path);
	if (len < 5 || path[len - 4] != '.' || path[len - 3] != 'c'
		|| path[len - 2] != 'u' || path[len - 1] != 'b')
		error_exit(g, "scene file must have a .cub extension");
}

/* Read the scene, parse the config block, then build and validate the map. */
void	parse_scene(t_game *g, const char *path)
{
	char	**lines;
	int		i;

	check_scene(g, path);
	lines = read_file(g, path);
	i = 0;
	while (lines[i] && (line_is_empty(lines[i]) || is_config_line(lines[i])))
	{
		if (!line_is_empty(lines[i]))
			parse_config(g, lines[i]);
		i++;
	}
	if (!g->tex_path[TEX_NO] || !g->tex_path[TEX_SO] || !g->tex_path[TEX_WE]
		|| !g->tex_path[TEX_EA] || !g->floor_set || !g->ceil_set)
	{
		free_split(lines);
		error_exit(g, "missing or incomplete scene configuration");
	}
	build_map(g, lines, i);
	free_split(lines);
	validate_map(g);
}
