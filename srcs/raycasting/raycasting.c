/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:06:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 11:33:48 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"



/*  creer une data_adr pour chaque image et les free a la fin + creer une variable pour les couleurs = eviter de recalculer 
*/
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
/*
void    draw_text(cube_t *c)
{
    double wallX; //where exactly the wall was hit
    if(c->side == 0 || c->side == 1) 
        wallX = c->posY + c->perpWallDist * c->rayDirY;
    else          
        wallX = c->posX + c->perpWallDist * c->rayDirX;
      wallX -= floor((wallX));
      //x coordinate on the texture
      int texX = (int)wallX * (double)c->texWidth;
      if((c->side == 0 || c->side == 1) && c->rayDirX > 0) 
        texX = c->texWidth - texX - 1;
      if((c->side == 2 || c->side == 3) && c->rayDirY < 0)
        texX = c->texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * c->texHeight / c->lineHeight;
      // Starting texture coordinate
      double texPos = (c->drawStart - c->reso[1] / 2 + c->lineHeight / 2) * step;
      int y = c->drawStart;
      if (c->side == 3)
        c->mlx_img_text = mlx_xpm_file_to_image(c->mlx_ptr, conf->no, &c->reso[0], &c->reso[1]);
      else if (c->side == 2)
        c->mlx_img_text = mlx_xpm_file_to_image(c->mlx_ptr, conf->so, &c->reso[0], &c->reso[1]);
      else if (c->side == 1)
        c->mlx_img_text = mlx_xpm_file_to_image(c->mlx_ptr, conf->ea, &c->reso[0], &c->reso[1]);
      else
        c->mlx_img_text = mlx_xpm_file_to_image(c->mlx_ptr, conf->we, &c->reso[0], &c->reso[1]);
      c->mlx_data = (int *)mlx_get_data_addr(conf->mlx_img_text, &(conf->bpp), &(conf->sizeLine), &(conf->endian));
      while (y < c->drawEnd)
      {
        int texY = (int)texPos & (c->texHeight - 1);
        texPos += step;
        c->color = c->mlx_data[c->texHeight * texY + texX];
        buffer[y][x] = color;
          y++;
      }
}*/

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
	while (i < c->drawStart)
	{
		c->mlx_data[i * c->reso[0] + x] = c->colorC;
		i++;
	}
	while (c->drawStart < c->drawEnd)
    {
        c->color = 0x0000FF; // OUEST
        if (c->side == 1)
            c->color = c->color / 2; // EST
        else if (c->side == 2)
            c->color = 0xFF3333; // rouge SUD
        else if (c->side == 3)
            c->color = 0X93FF33; //vert NORD
        c->mlx_data[c->drawStart++ * c->reso[0] + x] = c->color;
    }
    //ft_drawText(c);
	i = c->drawEnd;
	while (i < c->reso[1] - 1)
	{
		c->mlx_data[i * c->reso[0] + x] = c->colorF;
		i++;
    }
}

int		ft_raycasting(cube_t *conf)
{
    int x;

	x = 0;
    mlx_clear_window(conf->mlx_ptr, conf->mlx_win);
    while (x < conf->reso[0])
    {
        ft_initRaycast(x, conf);
		ft_draw1(conf);
		ft_draw2(conf);
		ft_draw3(x, conf);
        x++;
    }
	keyhooks(conf);
    mlx_put_image_to_window(conf->mlx_ptr, conf->mlx_win, conf->mlx_img, 0, 0);
	return (0);
}
