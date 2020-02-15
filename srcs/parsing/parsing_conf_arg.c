/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_conf_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 09:23:44 by alidy             #+#    #+#             */
/*   Updated: 2020/02/15 18:32:41 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_parsing_arg(int gc, char **gv)
{
	int		fd;
	int		i;

	fd = 0;
	i = 0;
	if (gc < 2 || gc > 3)
		ft_stderr(0, 0);
	if (gc == 3 && ft_memcmp(gv[2], "--save", 7) != 0)
		ft_stderr(0, 0);
	while (gv[1][i])
		i++;
	if (i > 4)
	{
		if (ft_memcmp(gv[1] + i - 4, ".cub", 5) != 0)
			ft_stderr(0, 0);
		if ((fd = open(gv[1], 'r')) < 0)
			ft_stderr(0, 0);
	}
	else
		ft_stderr(0, 0);
	return (fd);
}

int		ft_check_conf(t_cube *conf)
{
	if (conf->no && conf->so && conf->we && conf->ea && conf->s
	&& conf->f[0] != -1 && conf->c[0] != -1 && conf->reso[0])
		return (1);
	ft_stderr(1, conf);
	return (0);
}

int		ft_get_id(char *str, t_cube *conf)
{
	int		i;
	int		save;

	i = 0;
	save = 0;
	while (str[i] && str[i] == ' ')
		i++;
	save = i;
	while (str[i] && str[i] != ' ')
		i++;
	if (str[save] == '1' && ft_check_conf(conf))
		return (-1);
	else if (i - save > 2)
		ft_stderr(1, conf);
	else if (i == save)
		return (0);
	conf->temp = ft_substr(str, save, i - save);
	return (i);
}

void	ft_parsing_conf(char *line, t_cube *conf, int i)
{
	if (!ft_strncmp(conf->temp, "NO", 2))
		ft_parsing_path(line, conf, i, 1);
	else if (!ft_strncmp(conf->temp, "SO", 2))
		ft_parsing_path(line, conf, i, 2);
	else if (!ft_strncmp(conf->temp, "WE", 2))
		ft_parsing_path(line, conf, i, 3);
	else if (!ft_strncmp(conf->temp, "EA", 2))
		ft_parsing_path(line, conf, i, 4);
	else if (!ft_strncmp(conf->temp, "S", 2))
		ft_parsing_path(line, conf, i, 5);
	else if (!ft_strncmp(conf->temp, "F", 2))
		ft_parsing_color(line, conf, i, 1);
	else if (!ft_strncmp(conf->temp, "C", 2))
		ft_parsing_color(line, conf, i, 2);
	else if (!ft_strncmp(conf->temp, "R", 2))
		ft_parsing_screen(line, conf, i);
	else
		ft_stderr(1, conf);
}
