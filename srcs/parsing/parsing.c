/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 10:59:15 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 02:35:57 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_check_end_map(int fd, int res, char **line, cube_t *conf)
{
	int i;

	i = 0;
	ft_printf("ori: %c X : %d Y: %d",conf->ori,conf->posX,conf->posY);
	while (res > 0)
	{
		res = get_next_line(fd, line);
		if (!ft_check_after(*line, i))
			ft_stderr(5, conf);
		free(*line);
	}
	
	if (!conf->ori)
		ft_stderr(5, conf);
	close(fd);
}

void	ft_parsing_config(char **line, int fd, cube_t *conf, int *res)
{
	int id;

	id = 1;
	*res = 1;
	while (id >= 0 && *res > 0)
	{
		*res = get_next_line(fd, line);
		id = ft_get_id(*line, conf);
		if (id > 0)
		{
			ft_parsing_conf(*line, conf, id);
			free(conf->temp);
			conf->temp = 0;
		}
		if (id >= 0)
			free(*line);
	}
}

int		ft_check_one(cube_t *conf, int x, int y)
{
	int i;

	i = 0;
	while (i <= x)
	{
		if (conf->map[y][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i <= y)
	{
		if (conf->map[i][x] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	ft_fill_map(cube_t *conf)
{
	int x;
	int y;

	x = 0;
	y = 0;
	conf->map = ft_split(conf->temp, '\n');
	while (conf->map[y])
	{
		while (conf->map[y][x])
		{
			if (y == 0 || x == 0)
				if (conf->map[y][x] != '1')
					ft_stderr(5, conf);
			ft_get_start(conf, conf->map[y][x], x, y);
			x++;
		}
		if (y == 0)
			conf->lenX = x;
		else if (x != conf->lenX)
			ft_stderr(5, conf);
		x = 0;
		y++;
	}
	if (y < 3 || conf->lenX < 3 || ft_check_one(conf, conf->lenX - 1, y - 1))
		ft_stderr(5, conf);
}

void	ft_parsing_all(int gc, char **gv, cube_t *conf)
{
	char	*line;
	int		res;
	int		fd;
	int		check;
	int		end;

	check = 0;
	fd = ft_parsing_arg(gc, gv);
	end = 1;
	ft_parsing_config(&line, fd, conf, &res);
	if (res == 0)
		ft_stderr(5, conf);
	ft_parsing_map(line, conf, &check);
	while (res > 0 && end == 1)
	{
		res = get_next_line(fd, &line);
		end = ft_parsing_map(line, conf, &check);
		free(line);
	}
	ft_fill_map(conf);
	ft_check_end_map(fd, res, &line, conf);
}
