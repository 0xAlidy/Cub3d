/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_movement.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 16:50:07 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 17:46:54 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	up_move(cube_t *conf)
{
	int x;
	int y;

	x = (int)(conf->posX + conf->dirX * conf->moveSpeed);
	y = (int)(conf->posY + conf->dirY * conf->moveSpeed);
	if (conf->keyUp == 1 && conf->keyDown == 0)
	{
		if (conf->map[y][x] == '0')
		{
			conf->posX += conf->dirX * conf->moveSpeed;
			conf->posY += conf->dirY * conf->moveSpeed;
		}
	}
}

void	down_move(cube_t *conf)
{
	int x;
	int y;

	x = (int)(conf->posX - conf->dirX * conf->moveSpeed);
	y = (int)(conf->posY - conf->dirY * conf->moveSpeed);
	if (conf->keyDown == 1 && conf->keyUp == 0)
	{
		if (conf->map[y][x] == '0')
		{
			conf->posX -= conf->dirX * conf->moveSpeed;
			conf->posY -= conf->dirY * conf->moveSpeed;
		}
	}
}

void	right_move(cube_t *conf)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = conf->dirX;
	old_plane_x = conf->planeX;
	if (conf->keyRight == 1 && conf->keyLeft == 0)
	{
		conf->dirX = conf->dirX * cos(-conf->rotaSpeed) -
			conf->dirY * sin(-conf->rotaSpeed);
		conf->dirY = old_dir_x * sin(-conf->rotaSpeed) +
			conf->dirY * cos(-conf->rotaSpeed);
		conf->planeX = conf->planeX * cos(-conf->rotaSpeed) -
			conf->planeY * sin(-conf->rotaSpeed);
		conf->planeY = old_plane_x * sin(-conf->rotaSpeed) +
			conf->planeY * cos(-conf->rotaSpeed);
	}
}

void	left_move(cube_t *conf)
{
	float old_dir_x;
	float old_plane_x;

	old_dir_x = conf->dirX;
	old_plane_x = conf->planeX;
	if (conf->keyLeft == 1 && conf->keyRight == 0)
	{
		old_dir_x = conf->dirX;
		conf->dirX = conf->dirX * cos(conf->rotaSpeed)
		- conf->dirY * sin(conf->rotaSpeed);
		conf->dirY = old_dir_x * sin(conf->rotaSpeed) +
			conf->dirY * cos(conf->rotaSpeed);
		old_plane_x = conf->planeX;
		conf->planeX = conf->planeX * cos(conf->rotaSpeed)
		- conf->planeY * sin(conf->rotaSpeed);
		conf->planeY = old_plane_x * sin(conf->rotaSpeed) +
			conf->planeY * cos(conf->rotaSpeed);
	}
}

int		keyhooks(cube_t *conf)
{
	if (conf->keyUp == 1)
		up_move(conf);
	if (conf->keyDown == 1)
		down_move(conf);
	if (conf->keyLeft == 1)
		left_move(conf);
	if (conf->keyRight == 1)
		right_move(conf);
	return (0);
}
