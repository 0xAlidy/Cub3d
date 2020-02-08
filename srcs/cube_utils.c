/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 09:13:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 18:28:46 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_raycast(int x, cube_t *conf)
{
	conf->hit = 0;
	conf->cameraX = 2 * x / (double)conf->reso[0] - 1;
	conf->rayDirX = conf->dirX + conf->planeX * conf->cameraX;
	conf->rayDirY = conf->dirY + conf->planeY * conf->cameraX;
	conf->mapX = (int)conf->posX;
	conf->mapY = (int)conf->posY;
	conf->deltaDistX = fabs(1 / conf->rayDirX);
	conf->deltaDistY = fabs(1 / conf->rayDirY);
}

int		color(int r, int g, int b)
{
	int		color;

	color = 0;
	color += r * 256 * 256;
	color += g * 256;
	color += b;
	return (color);
}

void	ft_init_text(cube_t *c)
{
	c->textNo = mlx_xpm_file_to_image(c->mlx_ptr,
		c->no, &c->textWidth, &c->textHeight);
	c->textSo = mlx_xpm_file_to_image(c->mlx_ptr,
		c->so, &c->textWidth, &c->textHeight);
	c->textEa = mlx_xpm_file_to_image(c->mlx_ptr,
		c->ea, &c->textWidth, &c->textHeight);
	c->textWe = mlx_xpm_file_to_image(c->mlx_ptr,
		c->we, &c->textWidth, &c->textHeight);
	//c->textSprite = mlx_xpm_file_to_image(c->mlx_ptr,
		//c->s, &c->textWidth, &c->textHeight);
	c->dataNo = (int *)mlx_get_data_addr(c->textNo,
		&(c->bpp), &(c->sizeLine), &(c->endian));
	c->dataSo = (int *)mlx_get_data_addr(c->textSo,
		&(c->bpp), &(c->sizeLine), &(c->endian));
	c->dataEa = (int *)mlx_get_data_addr(c->textEa,
		&(c->bpp), &(c->sizeLine), &(c->endian));
	c->dataWe = (int *)mlx_get_data_addr(c->textWe,
		&(c->bpp), &(c->sizeLine), &(c->endian));
	//c->dataSprite = (int *)mlx_get_data_addr(c->textSprite,
		//&(c->bpp), &(c->sizeLine), &(c->endian));
}

void	ft_init_cube(cube_t *c)
{
	if ((c->mlx_ptr = mlx_init()) == NULL)
		ft_stderr(-1, c);
	c->mlx_img = mlx_new_image(c->mlx_ptr, c->reso[0], c->reso[1]);
	c->mlx_win = 0;
	c->sizeLine = c->reso[0] * 4;
	c->mlx_data = (int *)mlx_get_data_addr(c->mlx_img,
		&(c->bpp), &(c->sizeLine), &(c->endian));
	c->colorF = color(c->f[0], c->f[1], c->f[2]);
	c->colorC = color(c->c[0], c->c[1], c->c[2]);
	ft_init_text(c);
}

cube_t	ft_init_conf(void)
{
	cube_t	conf;

	conf.f[0] = -1;
	conf.f[1] = -1;
	conf.f[2] = -1;
	conf.c[0] = -1;
	conf.c[1] = -1;
	conf.c[2] = -1;
	conf.endian = 1;
	conf.dirX = 0;
	conf.dirY = -1;
	conf.planeX = 0.66;
	conf.planeY = 0;
	conf.bpp = 32;
	conf.rotaSpeed = 0.06;
	conf.moveSpeed = 0.06;
	conf.textWidth = 400;
	conf.textHeight = 400;
	return (conf);
}
