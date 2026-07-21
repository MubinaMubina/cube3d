/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/16 00:00:00 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Count the number of lines a '\n'-separated string splits into. */
int	count_nl(const char *s)
{
	int	i;
	int	lines;

	i = 0;
	lines = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			lines++;
		i++;
	}
	if (i > 0 && s[i - 1] != '\n')
		lines++;
	return (lines);
}

/* Duplicate len bytes of s into a fresh NUL-terminated string. */
static char	*dup_line(t_game *g, const char *s, int len)
{
	char	*line;
	int		i;

	line = malloc(len + 1);
	if (!line)
		error_exit(g, "allocation failed");
	i = 0;
	while (i < len)
	{
		line[i] = s[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

/* Split content on '\n' into the pre-allocated lines array. */
void	fill_lines(t_game *g, char *content, char **lines)
{
	int	i;
	int	start;
	int	idx;

	i = 0;
	start = 0;
	idx = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			lines[idx++] = dup_line(g, content + start, i - start);
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		lines[idx++] = dup_line(g, content + start, i - start);
	lines[idx] = NULL;
}
