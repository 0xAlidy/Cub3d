/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 09:21:32 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 22:05:32 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_fill_rgb(int nb, t_cube *conf, int num, int cpt)
{
	if (nb < 0 || nb > 255)
		ft_stderr(4, conf);
	if (num == 1 && conf->f[cpt] == -1)
		conf->f[cpt] = nb;
	else if (num == 2 && conf->c[cpt] == -1)
		conf->c[cpt] = nb;
	else
		ft_stderr(4, conf);
}

void	ft_test_color(int i, char *str, t_cube *conf)
{
	int cpt;
	int check;
	int cunt;

	cpt = 0;
	check = 1;
	cunt = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',' && str[i] != ' ')
			ft_stderr(4, conf);
		if (str[i] >= '0' && str[i] <= '9' && check == 1)
		{
			check = 0;
			cunt++;
		}
		if (str[i] == ',')
		{
			check = 1;
			cpt++;
		}
		i++;
	}
	if (cpt != 2 || cunt != 3)
		ft_stderr(4, conf);
}

void	ft_parsing_color(char *line, t_cube *conf, int i, int nb)
{
	int		save;
	int		res;
	int		cpt;

	res = 0;
	save = 0;
	cpt = -1;
	while (line[i] && line[i] == ' ')
		i++;
	ft_test_color(i, line, conf);
	while (line[i])
	{
		save = i;
		while (line[i] && line[i] != ',' && line[i] != ' ')
			i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == ',')
			i++;
		while (line[i] == ' ')
			i++;
		res = atoi(line + save);
		cpt++;
		ft_fill_rgb(res, conf, nb, cpt);
	}
}
