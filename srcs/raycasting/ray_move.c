/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:20:44 by alidy             #+#    #+#             */
/*   Updated: 2020/02/17 19:21:03 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	right_rota(t_cube *conf)
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

void	left_rota(t_cube *conf)
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
