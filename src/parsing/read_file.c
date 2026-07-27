/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmubina <mmubina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:00:00 by mmubina           #+#    #+#             */
/*   Updated: 2026/07/21 18:51:43 by mmubina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*append_chunk(t_game *g, char *dst, char *buf, int n)
{
	size_t	old;
	char	*res;
	size_t	i;

	old = 0;
	if (dst)
		old = str_len(dst);
	res = malloc(old + n + 1);
	if (!res)
		error_exit(g, "allocation failed");
	i = 0;
	while (i < old)
	{
		res[i] = dst[i];
		i++;
	}
	i = 0;
	while (i < (size_t)n)
	{
		res[old + i] = buf[i];
		i++;
	}
	res[old + n] = '\0';
	free(dst);
	return (res);
}

static char	*read_all(t_game *g, int fd)
{
	char	buf[4096];
	char	*content;
	int		n;

	content = NULL;
	n = read(fd, buf, 4096);
	while (n > 0)
	{
		content = append_chunk(g, content, buf, n);
		n = read(fd, buf, 4096);
	}
	if (n < 0)
		error_exit(g, "read failed");
	if (!content)
		content = str_dup(g, "");
	return (content);
}

char	**read_file(t_game *g, const char *path)
{
	int		fd;
	char	*content;
	char	**lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit(g, "cannot open scene file");
	content = read_all(g, fd);
	close(fd);
	lines = malloc(sizeof(char *) * (count_nl(content) + 1));
	if (!lines)
		error_exit(g, "allocation failed");
	fill_lines(g, content, lines);
	free(content);
	return (lines);
}
