/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:06:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 20:54:37 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_initRaycast(int x, cube_t *conf)
{
	conf->hit = 0;
	conf->cameraX = 2 * x / (double)conf->reso[0] - 1;
    conf->rayDirX = conf->dirX + conf->planeX * conf->cameraX ;
    conf->rayDirY = conf->dirY + conf->planeY * conf->cameraX ;
    conf->mapX = (int)conf->posX;
    conf->mapY = (int)conf->posY;
    conf->deltaDistX = fabs(1 / conf->rayDirX);
    conf->deltaDistY = fabs(1 / conf->rayDirY);
}

void	ft_draw1(cube_t *conf)
{
	if (conf->rayDirX < 0)
    {
        conf->stepX = -1;
        conf->sideDistX = (conf->posX - conf->mapX) * conf->deltaDistX;
    }
    else
    {
        conf->stepX = 1;
        conf->sideDistX = (conf->mapX + 1.0 - conf->posX) * conf->deltaDistX;
    }
    if (conf->rayDirY < 0)
    {
    	conf->stepY = -1;
        conf->sideDistY = (conf->posY - conf->mapY) * conf->deltaDistY;
    }
    else
    {
        conf->stepY = 1;
        conf->sideDistY = (conf->mapY + 1.0 - conf->posY) * conf->deltaDistY;
    }
}

void	ft_draw2(cube_t *conf)
{
	while (conf->hit == 0)
    {
        if (conf->sideDistX < conf->sideDistY)
        {
            conf->sideDistX += conf->deltaDistX;
            conf->mapX += conf->stepX;    
            conf->side = 0;
        }   
        else
        {
            conf->sideDistY += conf->deltaDistY;
            conf->mapY += conf->stepY;
            conf->side = 2;
        }
        if (conf->map[conf->mapY][conf->mapX] == '1')
        {
            conf->hit = 1;
           // printf("rayDirX: %f rayDirY: %f\n",conf->rayDirX,conf->rayDirY);
           if (conf->side == 0)
           {
               if (conf->mapX < conf->posX)
                conf->side = 1;
           }
           else
           {
               if (conf->mapY < conf->posY)
                conf->side = 3;
           }
        }
    }
}

void	ft_draw3(int x, cube_t *c)
{
	int i;

	i = 0;
	if (c->side == 0 || c->side == 1) 
        c->perpWallDist = (c->mapX - c->posX + (1 - c->stepX) / 2) / c->rayDirX;
    else          
        c->perpWallDist = (c->mapY - c->posY + (1 - c->stepY) / 2) / c->rayDirY;
    c->lineHeight = (long int)(c->reso[1] / c->perpWallDist);
    c->drawStart = -c->lineHeight / 2 + c->reso[1] / 2; 
    if (c->drawStart <  0) 
        c->drawStart = 0;
    c->drawEnd = c->lineHeight / 2 + c->reso[1] / 2;
    if (c->drawEnd >= c->reso[1])
        c->drawEnd = c->reso[1] - 1;
    c->color = 0x0000FF; // 
    if (c->side == 1)
        c->color = c->color / 2;
    else if (c->side == 2)
        c->color = 0xFF3333; // rouge 
    else if (c->side == 3)
        c->color = 0X93FF33; //vert
	while (i < c->drawStart)
	{
		c->mlx_data[i * c->reso[0] + x] = color(c->c[0], c->c[1], c->c[2]);
		i++;
	}
	while (c->drawStart < c->drawEnd)
		c->mlx_data[c->drawStart++ * c->reso[0] + x] = c->color;
	i = c->drawEnd;
	while (i < c->reso[1] - 1)
	{
		c->mlx_data[i * c->reso[0] + x] = color(c->f[0], c->f[1], c->f[2]);
		i++;
    }
}

int		ft_raycasting(cube_t *conf)
{
    int x;

	x = 0;
    while (x < conf->reso[0])
    {
        ft_initRaycast(x, conf);
		ft_draw1(conf);
		ft_draw2(conf);
		ft_draw3(x, conf);
        x++;
    }
	keyhooks(conf);
	mlx_clear_window(conf->mlx_ptr, conf->mlx_win);
    mlx_put_image_to_window(conf->mlx_ptr, conf->mlx_win, conf->mlx_img, 0, 0);
	return (0);
}
