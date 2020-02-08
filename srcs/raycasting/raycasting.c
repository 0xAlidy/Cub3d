/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:06:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 18:30:34 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			if (conf->side == 0 && conf->mapX < conf->posX)
				conf->side = 1;
			else if (conf->side != 0 && conf->mapY < conf->posY)
				conf->side = 3;
		}
	}
}

void	ft_choose_text(cube_t *c)
{
	if (c->side == 3)
		c->dataText = c->dataNo;
	else if (c->side == 2)
		c->dataText = c->dataSo;
	else if (c->side == 1)
		c->dataText = c->dataWe;
	else
		c->dataText = c->dataEa;
}

void	ft_draw_text(int x, cube_t *c)
{
	double	tex_pos;
	double	step;
	int		y;

	y = c->drawStart - 1;
	if (c->side == 0 || c->side == 1)
		c->wall_x = c->posY + c->perpWallDist * c->rayDirY;
	else
		c->wall_x = c->posX + c->perpWallDist * c->rayDirX;
	c->wall_x -= floor((c->wall_x));
	c->tex_x = c->wall_x * (double)c->textWidth;
	if ((c->side == 0 || c->side == 1) && c->rayDirX > 0)
		c->tex_x = c->textWidth - c->tex_x - 1;
	if ((c->side == 2 || c->side == 3) && c->rayDirY < 0)
		c->tex_x = c->textWidth - c->tex_x - 1;
	step = 1.0 * c->textHeight / c->lineHeight;
	tex_pos = (c->drawStart - c->reso[1] / 2 + c->lineHeight / 2) * step;
	ft_choose_text(c);
	while (++y < c->drawEnd)
	{
		c->tex_y = (int)tex_pos;
		tex_pos += step;
		c->color = c->dataText[c->textHeight * c->tex_y + c->tex_x];
		c->mlx_data[y * c->reso[0] + x] = c->color;
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
	if (c->drawStart < 0)
		c->drawStart = 0;
	c->drawEnd = c->lineHeight / 2 + c->reso[1] / 2;
	if (c->drawEnd >= c->reso[1])
		c->drawEnd = c->reso[1] - 1;
	while (i < c->drawStart)
	{
		c->mlx_data[i * c->reso[0] + x] = c->colorC;
		i++;
	}
	ft_draw_text(x, c);
	i = c->drawEnd - 1;
	while (++i < c->reso[1] - 1)
		c->mlx_data[i * c->reso[0] + x] = c->colorF;
}
