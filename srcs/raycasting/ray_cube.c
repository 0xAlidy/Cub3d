/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_cube.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:35:16 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 17:38:16 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_define_movement(int key, cube_t *conf)
{
	if (key == 53)
		ft_close_mlx(conf);
	if (key == 126 || key == 13)
		conf->keyUp = 1;
	if (key == 125 || key == 1)
		conf->keyDown = 1;
	if (key == 123 || key == 0)
		conf->keyRight = 1;
	if (key == 124 || key == 2)
		conf->keyLeft = 1;
	keyhooks(conf);
	return (0);
}

int		ft_reset_movement(int key, cube_t *conf)
{
	if (key == 126 || key == 13)
		conf->keyUp = 0;
	if (key == 125 || key == 1)
		conf->keyDown = 0;
	if (key == 123 || key == 0)
		conf->keyRight = 0;
	if (key == 124 || key == 2)
		conf->keyLeft = 0;
	return (0);
}

void	ft_start_rota(cube_t *conf)
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
	old_dir_x = conf->dirX;
	old_plane_x = conf->planeX;
	conf->dirX = conf->dirX * cos(-rota) - conf->dirY * sin(-rota);
	conf->dirY = old_dir_x * sin(-rota) + conf->dirY * cos(-rota);
	conf->planeX = conf->planeX * cos(-rota) - conf->planeY * sin(-rota);
	conf->planeY = old_plane_x * sin(-rota) + conf->planeY * cos(-rota);
}

void	ft_change_start(cube_t *conf, int x, int y)
{
	if (conf->posX == 1 && conf->posY == 1)
	{
		conf->posX += 0.0001;
		conf->posY += 0.0001;
	}
	else if (conf->posX == 1 && conf->posY == y - 2)
	{
		conf->posX += 0.0001;
		conf->posY += 0.9999;
	}
	else if (conf->posX == x - 2 && conf->posY == 1)
	{
		conf->posX += 0.9999;
		conf->posY += 0.0001;
	}
	else if (conf->posX == x - 2 && conf->posY == y - 2)
	{
		conf->posX += 0.9999;
		conf->posY += 0.9999;
	}
}

void	ft_start_move(cube_t *conf)
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
