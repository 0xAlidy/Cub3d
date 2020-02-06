/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_movement.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 16:50:07 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:06:47 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	upMove(cube_t *conf)
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

void	downMove(cube_t *conf)
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

void	rightMove(cube_t *conf)
{
    float oldDirX;
    float oldplaneX;

    oldDirX = conf->dirX;
    oldplaneX = conf->planeX;
	if (conf->keyRight == 1 && conf->keyLeft == 0)
	{
		conf->dirX = conf->dirX * cos(-conf->rotaSpeed) - 
            conf->dirY * sin(-conf->rotaSpeed);
		conf->dirY = oldDirX * sin(-conf->rotaSpeed) + 
            conf->dirY * cos(-conf->rotaSpeed);
		conf->planeX = conf->planeX * cos(-conf->rotaSpeed) -
			conf->planeY * sin(-conf->rotaSpeed);
		conf->planeY = oldplaneX * sin(-conf->rotaSpeed) +
			conf->planeY * cos(-conf->rotaSpeed);
	}
}

void	leftMove(cube_t *conf)
{
    float oldDirX;
    float oldplaneX;
		
    oldDirX = conf->dirX;
    oldplaneX = conf->planeX;
	if (conf->keyLeft == 1 && conf->keyRight == 0)
	{
		oldDirX = conf->dirX;
		conf->dirX = conf->dirX * cos(conf->rotaSpeed) - conf->dirY * sin(conf->rotaSpeed);
		conf->dirY = oldDirX * sin(conf->rotaSpeed) +
			conf->dirY * cos(conf->rotaSpeed);
		oldplaneX = conf->planeX;
		conf->planeX = conf->planeX * cos(conf->rotaSpeed) - conf->planeY * sin(conf->rotaSpeed);
		conf->planeY = oldplaneX * sin(conf->rotaSpeed) +
			conf->planeY * cos(conf->rotaSpeed);
	}
}

int		keyhooks(cube_t *conf)
{
	if (conf->keyUp == 1)
		upMove(conf);
	if (conf->keyDown == 1)
		downMove(conf);
	if (conf->keyLeft == 1)
		leftMove(conf);
	if (conf->keyRight == 1)
		rightMove(conf);
	return (0);
}
