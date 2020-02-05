/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 02:14:26 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 15:26:05 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../minilibx/mlx.h"

int     redraw(cube_t *conf);

int		color(int r, int g, int b)
{
	int		color;

	color = 0;
	color += r * 256 * 256;
	color += g * 256;
	color += b;
	return (color);
}

int		close_win(cube_t *conf)
{
	mlx_destroy_window(conf->mlx_ptr, conf->mlx_win);
	exit(EXIT_SUCCESS);
    return (0);
}

void	upmove(cube_t *conf)
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
				redraw(conf);
			}
		}
	}

	void	downmove(cube_t *conf)
	{
		int x;
		int y;

		x = (int)(conf->posX - conf->dirX * conf->moveSpeed);
		y = (int)(conf->posY - conf->dirY * conf->moveSpeed);
		if (conf->keyDown == 1 & conf->keyUp == 0)
		{
			if (conf->map[y][x] == '0')
			{
				conf->posX -= conf->dirX * conf->moveSpeed;
				conf->posY -= conf->dirY * conf->moveSpeed;
				redraw(conf);
			}
		}
	}

	void	rightmove(cube_t *conf)
	{
        float oldDirX;
        float oldplaneX;

        oldDirX = conf->dirX;
        oldplaneX = conf->planeX;
		if (conf->keyRight == 1 && conf->keyLeft == 0)
		{
			conf->dirX = conf->dirX * cos(-conf->rotaSpeed) - conf->dirY * sin(-conf->rotaSpeed);
			conf->dirY = oldDirX * sin(-conf->rotaSpeed) + conf->dirY * cos(-conf->rotaSpeed);
			conf->planeX = conf->planeX * cos(-conf->rotaSpeed) -
				conf->planeY * sin(-conf->rotaSpeed);
			conf->planeY = oldplaneX * sin(-conf->rotaSpeed) +
				conf->planeY * cos(-conf->rotaSpeed);
			redraw(conf);
		}
	}

	void	leftmove(cube_t *conf)
	{
        float oldDirX;
        float oldplaneX;

        oldDirX = conf->dirX;
        oldplaneX = conf->planeX;
		if (conf->keyRight == 1 && conf->keyRight == 0)
		{
			oldDirX = conf->dirX;
			conf->dirX = conf->dirX * cos(conf->rotaSpeed) - conf->dirY * sin(conf->rotaSpeed);
			conf->dirY = oldDirX * sin(conf->rotaSpeed) +
				conf->dirY * cos(conf->rotaSpeed);
			oldplaneX = conf->planeX;
			conf->planeX = conf->planeX * cos(conf->rotaSpeed) - conf->planeY * sin(conf->rotaSpeed);
			conf->planeY = oldplaneX * sin(conf->rotaSpeed) +
				conf->planeY * cos(conf->rotaSpeed);
			redraw(conf);
		}
	}

	int		keyhooks(int key, cube_t *conf)
	{
		if (key == 53)
			exit(EXIT_SUCCESS);
		else if (conf->keyUp == 1)
			upmove(conf);
		else if (conf->keyDown == 1)
			downmove(conf);
		else if (conf->keyLeft == 1)
			leftmove(conf);
		else if (conf->keyRight == 1)
			rightmove(conf);
		return (0);
	}
	int		vaultmovement(int key, cube_t *conf)
	{
		if (key == 126 || key == 13)
			conf->keyUp = 1;
		else if (key == 125 || key == 1)
			conf->keyDown = 1;
		else if (key == 123 || key == 0)
			conf->keyLeft = 1;
		else if (key == 124 || key == 2)
			conf->keyRight = 1;
		keyhooks(key, conf);
		return (0);
	}

	int		vaultmovementtoggle(int key, cube_t *conf)
	{
		if (key == 126 || key == 13)
			conf->keyUp = 0;
		else if (key == 125 || key == 1)
			conf->keyDown = 0;
		else if (key == 123 || key == 0)
			conf->keyLeft = 0;
		else if (key == 124 || key == 2)
			conf->keyRight = 0;
		keyhooks(key, conf);
		return (0);
	}

int		repeat(cube_t *conf)
{
		mlx_hook(conf->mlx_win, 2, 0, vaultmovement, &conf);
		mlx_hook(conf->mlx_win, 3, 0, vaultmovementtoggle, &conf);
		mlx_hook(conf->mlx_win, 17, 0, close_win, &conf);
		return (0);
}

int     redraw(cube_t *conf)
{
    int x;
    int i;

    x = 0;
    while (x < conf->reso[0])
    {
        i = 0;
        conf->cameraX = 2 * x / (double)conf->reso[0] - 1;
        conf->rayDirX = conf->dirX + conf->planeX * conf->cameraX;
        conf->rayDirY = conf->dirY + conf->planeY * conf->cameraX;
        conf->mapX = (int)conf->posX;
        conf->mapY = (int)conf->posY;
        conf->deltaDistX = fabs(1 / conf->rayDirX);
        conf->deltaDistY = fabs(1 / conf->rayDirY);
        conf->hit = 0;
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
                conf->side = 1;
            }
            if (conf->map[conf->mapY][conf->mapX] == '1')
                conf->hit = 1;
        }
        if (conf->side == 0) 
            conf->perpWallDist = (conf->mapX - conf->posX + (1 - conf->stepX) / 2) / conf->rayDirX;
        else          
            conf->perpWallDist = (conf->mapY - conf->posY + (1 - conf->stepY) / 2) / conf->rayDirY;
        //dprintf(1,"%f",conf->perpWallDist);
        conf->lineHeight = (long int)(conf->reso[1] / conf->perpWallDist);
        conf->drawStart = -conf->lineHeight / 2 + conf->reso[1] / 2; 
        if (conf->drawStart <  0) 
            conf->drawStart = 0;
        conf->drawEnd = conf->lineHeight / 2 + conf->reso[1] / 2;
        if (conf->drawEnd >= conf->reso[1])
            conf->drawEnd = conf->reso[1] - 1;
        conf->color = 0x0000FF;
        if (conf->side == 1)
            conf->color = conf->color / 2;
		while (i < conf->drawStart)
		{
			conf->mlx_data[i * conf->reso[0] + x] = color(conf->c[0], conf->c[1], conf->c[2]);
			i++;
		}
		while (conf->drawStart < conf->drawEnd)
			conf->mlx_data[conf->drawStart++ * conf->reso[0] + x] = conf->color;
		i = conf->drawEnd;
		while (i < conf->reso[1] - 1)
		{
			conf->mlx_data[i * conf->reso[0] + x] = color(conf->f[0], conf->f[1], conf->f[2]);
			i++;
        }
        x++;
    }
    mlx_clear_window(conf->mlx_ptr, conf->mlx_win);
    mlx_put_image_to_window(conf->mlx_ptr, conf->mlx_win, conf->mlx_img, 0, 0);
    return (0);
}

int main(int gc, char **gv)
{
    cube_t		conf;
    
    conf = ft_init_conf();
    ft_parsing_all(gc, gv, &conf);
    if ((conf.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((conf.mlx_win = mlx_new_window(conf.mlx_ptr, conf.reso[0], conf.reso[1], "Cub3D")) == NULL)
        return (EXIT_FAILURE);
    conf.mlx_img = mlx_new_image(conf.mlx_ptr, conf.reso[0], conf.reso[1]);
    conf.sizeLine = conf.reso[0] * 4;
    conf.mlx_data = (int *)mlx_get_data_addr(conf.mlx_img, &(conf.bpp), &(conf.sizeLine), &(conf.endian));
    redraw(&conf);
    //mlx_clear_window(conf.mlx_ptr, conf.mlx_win);
   //mlx_put_image_to_window(conf.mlx_ptr, conf.mlx_win, conf.mlx_img, 0, 0);
    mlx_loop_hook(conf.mlx_ptr, repeat, &conf);
    mlx_loop(conf.mlx_ptr);
    return (EXIT_SUCCESS);
}
