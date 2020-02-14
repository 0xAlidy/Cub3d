/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_cube.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:35:16 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 22:40:18 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
	if (key == 123 || key == 0)
		conf->k_right = 1;
	if (key == 124 || key == 2)
		conf->k_left = 1;
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

void	ft_change_start(t_cube *conf, int x, int y)
{
	
	if (conf->pos_x == 1 && conf->pos_y == y - 2)
	{
		conf->pos_x += 0.0001;
		conf->pos_y += 0.9999;
	}
	else if (conf->pos_x == x - 2 && conf->pos_y == 1)
	{
		conf->pos_x += 0.9999;
		conf->pos_y += 0.0001;
	}
	else if (conf->pos_x == x - 2 && conf->pos_y == y - 2)
	{
		conf->pos_x += 0.9999;
		conf->pos_y += 0.9999;
	}
	else
	{
		conf->pos_x += 0.0001;
		conf->pos_y += 0.0001;
	}
}

void	ft_start_move(t_cube *conf)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (conf->map[0][x])
		x++;
	while (conf->map[y])
		y++;
	ft_change_start(conf, x, y);
}
