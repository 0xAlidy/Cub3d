/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_cube.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:35:16 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:23:45 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_defineMovement(int key, cube_t *conf)
{
	if (key == 53)
		ft_closeWin(conf);
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

int		ft_resetMovement(int key, cube_t *conf)
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

int		color(int r, int g, int b)
{
	int		color;

	color = 0;
	color += r * 256 * 256;
	color += g * 256;
	color += b;
	return (color);
}

void	ft_startRota(cube_t *conf)
{
    float 	oldDirX;
    float 	oldplaneX;
	float	rota;

	rota = 0;
	if (conf->ori == 'W')
		rota = 1.58;
	else if (conf->ori == 'S')
		rota = 3.14;
	else if (conf->ori == 'E')
		rota = 4.71;
    oldDirX = conf->dirX;
    oldplaneX = conf->planeX;
	conf->dirX = conf->dirX * cos(-rota) - conf->dirY * sin(-rota);
	conf->dirY = oldDirX * sin(-rota) + conf->dirY * cos(-rota);
	conf->planeX = conf->planeX * cos(-rota) - conf->planeY * sin(-rota);
	conf->planeY = oldplaneX * sin(-rota) + conf->planeY * cos(-rota);
}

void	ft_startMove(cube_t *c)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (c->map[0][x])
		x++;
	while (c->map[y])
		y++;
	if (c->posX == 1 && c->posY == 1)
	{
		c->posX += 0.0001;
		c->posY += 0.0001; 
	}
	else if (c->posX == 1 && c->posY == y - 2)
	{
		c->posX += 0.0001;
		c->posY += 0.9999;
	}
	else if (c->posX == x - 2 && c->posY == 1)
	{
		c->posX += 0.9999;
		c->posY += 0.0001;
	}
	else if (c->posX == x - 2 && c->posY == y - 2)
	{
		c->posX += 0.9999;
		c->posY += 0.9999;
	}
}

void    ft_game(cube_t *c)
{
    if ((c->mlx_ptr = mlx_init()) == NULL)
        ft_stderr(-1, c);
    if ((c->mlx_win = mlx_new_window(c->mlx_ptr, c->reso[0], c->reso[1], "Cub3D")) == NULL)
        ft_stderr(-1, c);
    c->mlx_img = mlx_new_image(c->mlx_ptr, c->reso[0], c->reso[1]);
    c->sizeLine = c->reso[0] * 4;
    c->mlx_data = (int *)mlx_get_data_addr(c->mlx_img, &(c->bpp), &(c->sizeLine), &(c->endian));
	c->colorF = color(c->f[0], c->f[1], c->f[2]);
	c->colorC = color(c->c[0], c->c[1], c->c[2]);
    c->textNo = mlx_xpm_file_to_image(c->mlx_ptr, c->no, &c->textWidth, &c->textHeight);
    c->textSo = mlx_xpm_file_to_image(c->mlx_ptr, c->so, &c->textWidth, &c->textHeight);
    c->textEa = mlx_xpm_file_to_image(c->mlx_ptr, c->ea, &c->textWidth, &c->textHeight);
    c->textWe = mlx_xpm_file_to_image(c->mlx_ptr, c->we, &c->textWidth, &c->textHeight);
	c->dataNo = (int *)mlx_get_data_addr(c->textNo, &(c->bpp), &(c->sizeLine), &(c->endian));
	c->dataSo = (int *)mlx_get_data_addr(c->textSo, &(c->bpp), &(c->sizeLine), &(c->endian));
	c->dataEa = (int *)mlx_get_data_addr(c->textEa, &(c->bpp), &(c->sizeLine), &(c->endian));
	c->dataWe = (int *)mlx_get_data_addr(c->textWe, &(c->bpp), &(c->sizeLine), &(c->endian));
	ft_startRota(c);
	ft_startMove(c);
    mlx_loop_hook(c->mlx_ptr, ft_raycasting, c);
	mlx_hook(c->mlx_win, 2, 0, ft_defineMovement, c);
	mlx_hook(c->mlx_win, 3, 0, ft_resetMovement, c);
	mlx_hook(c->mlx_win, 17, 0, ft_closeWin, c);
    mlx_loop(c->mlx_ptr);
}
