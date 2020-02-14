/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 09:20:43 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:05:28 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_check_ori(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	ft_get_start(t_cube *conf, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		conf->ori = c;
		conf->pos_x = x;
		conf->pos_y = y;
		conf->map[y][x] = '0';
	}
}

int		ft_parsing_m(t_cube *conf, char *line, int *check)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if ((line[i] >= '0' && line[i] <= '2'))
		{
			i++;
			len++;
		}
		else if (ft_check_ori(line[i]) && (*check) == 0)
		{
			(*check) = 1;
			i++;
			len++;
		}
		else if (line[i] == ' ')
			i++;
		else
			ft_stderr(5, conf);
	}
	return (len);
}

int		ft_parsing_map(char *line, t_cube *conf, int *check)
{
	int		i;
	int		len;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if ((len = ft_parsing_m(conf, line, check)) == 0)
		return (0);
	if (!(str = malloc(len + 1 * sizeof(char))))
		ft_stderr(-1, conf);
	str[len] = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			str[j] = line[i];
			j++;
		}
		i++;
	}
	conf->temp = ft_strjoin_free(conf->temp, str, 3);
	conf->temp = ft_strjoin_free(conf->temp, "\n", 1);
	return (1);
}
