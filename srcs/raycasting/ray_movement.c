/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_movement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:50:07 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 18:05:12 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	up_move(t_cube *conf)
{
	int x;
	int y;

	x = (int)(conf->pos_x + conf->dir_x * conf->move_s);
	y = (int)(conf->pos_y + conf->dir_y * conf->move_s);
	if (conf->k_up == 1 && conf->k_down == 0)
	{
		if (conf->map[y][x] == '0')
		{
			conf->pos_x += conf->dir_x * conf->move_s;
			conf->pos_y += conf->dir_y * conf->move_s;
		}
	}
}

void	down_move(t_cube *conf)
{
	int x;
	int y;

	x = (int)(conf->pos_x - conf->dir_x * conf->move_s);
	y = (int)(conf->pos_y - conf->dir_y * conf->move_s);
	if (conf->k_down == 1 && conf->k_up == 0)
	{
		if (conf->map[y][x] == '0')
		{
			conf->pos_x -= conf->dir_x * conf->move_s;
			conf->pos_y -= conf->dir_y * conf->move_s;
		}
	}
}

void	right_move(t_cube *conf)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = conf->dir_x;
	old_plane_x = conf->plane_x;
	if (conf->k_right == 1 && conf->k_left == 0)
	{
		conf->dir_x = conf->dir_x * cos(-conf->rota_s) -
			conf->dir_y * sin(-conf->rota_s);
		conf->dir_y = old_dir_x * sin(-conf->rota_s) +
			conf->dir_y * cos(-conf->rota_s);
		conf->plane_x = conf->plane_x * cos(-conf->rota_s) -
			conf->plane_y * sin(-conf->rota_s);
		conf->plane_y = old_plane_x * sin(-conf->rota_s) +
			conf->plane_y * cos(-conf->rota_s);
	}
}

void	left_move(t_cube *conf)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = conf->dir_x;
	old_plane_x = conf->plane_x;
	if (conf->k_left == 1 && conf->k_right == 0)
	{
		old_dir_x = conf->dir_x;
		conf->dir_x = conf->dir_x * cos(conf->rota_s)
		- conf->dir_y * sin(conf->rota_s);
		conf->dir_y = old_dir_x * sin(conf->rota_s) +
			conf->dir_y * cos(conf->rota_s);
		old_plane_x = conf->plane_x;
		conf->plane_x = conf->plane_x * cos(conf->rota_s)
		- conf->plane_y * sin(conf->rota_s);
		conf->plane_y = old_plane_x * sin(conf->rota_s) +
			conf->plane_y * cos(conf->rota_s);
	}
}

int		keyhooks(t_cube *conf)
{
	if (conf->k_up == 1)
		up_move(conf);
	if (conf->k_down == 1)
		down_move(conf);
	if (conf->k_left == 1)
		left_move(conf);
	if (conf->k_right == 1)
		right_move(conf);
	return (0);
}
