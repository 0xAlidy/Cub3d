/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cube.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:02:18 by alidy             #+#    #+#             */
/*   Updated: 2020/02/18 21:02:33 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_define_movement(int key, t_cube *conf)
{
	if (key == 53)
		ft_close_mlx(conf);
	if (key == 126 || key == 13)
		conf->k_up = 1;
	if (key == 125 || key == 1)
		conf->k_down = 1;
	if (key == 123)
		conf->k_right = 1;
	if (key == 0)
		conf->k_right = 2;
	if (key == 124)
		conf->k_left = 1;
	if (key == 2)
		conf->k_left = 2;
	keyhooks(conf);
	return (0);
}

int		ft_reset_movement(int key, t_cube *conf)
{
	if (key == 126 || key == 13)
		conf->k_up = 0;
	if (key == 125 || key == 1)
		conf->k_down = 0;
	if (key == 123 || key == 0)
		conf->k_right = 0;
	if (key == 124 || key == 2)
		conf->k_left = 0;
	return (0);
}

void	ft_start_rota(t_cube *conf)
{
	float	old_dir_x;
	float	old_plane_x;
	float	rota;

	rota = 0;
	if (conf->ori == 'W')
		rota = 1.58;
	else if (conf->ori == 'S')
		rota = 3.14;
	else if (conf->ori == 'E')
		rota = 4.71;
	old_dir_x = conf->dir_x;
	old_plane_x = conf->plane_x;
	conf->dir_x = conf->dir_x * cos(-rota) - conf->dir_y * sin(-rota);
	conf->dir_y = old_dir_x * sin(-rota) + conf->dir_y * cos(-rota);
	conf->plane_x = conf->plane_x * cos(-rota) - conf->plane_y * sin(-rota);
	conf->plane_y = old_plane_x * sin(-rota) + conf->plane_y * cos(-rota);
}

void	ft_change_start(t_cube *conf)
{
	conf->pos_x += 0.50;
	conf->pos_y += 0.50;
}
