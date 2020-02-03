/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 02:14:26 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 15:30:39 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../minilibx/mlx.h"

unsigned int	colormagic(int i, double x, double y, cube_t *conf)
	{
		unsigned int	color;
		float			magic;
		float			i2;

		magic = sqrt(x * x + y * y);
		i2 = i + 1 - (log(2) / magic) / log(2);
		conf->chan[0] = (unsigned char)(sin(0.026 * i2 + 4) * 230 + 25);
		conf->chan[1] = (unsigned char)(sin(0.023 * i2 + 2) * 230 + 25);
		conf->chan[2] = (unsigned char)(sin(0.01 * i2 + 1) * 230 + 25);
		color = (conf->chan[0] << 16) + (conf->chan[1] << 8) + (conf->chan[2] + 255);
		return (color);
	}

void	colorpick(cube_t *conf)
	{
		char initio;

		initio = conf->map[conf->mapY][conf->mapX];
		if (initio == '1')
			conf->color = 0x00FFFF;
		else if (initio == '0')
			conf->color = 0x008080;
	}

int main(int gc, char **gv)
{
    cube_t		conf;
    int         x;

    x = 0;
    conf = ft_init_conf();
    ft_parsing_all(gc, gv, &conf);
    if ((conf.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((conf.mlx_win = mlx_new_window(conf.mlx_ptr, conf.reso[0], conf.reso[1], "Cub3D")) == NULL)
        return (EXIT_FAILURE);
    conf.mlx_img = mlx_new_image(conf.mlx_ptr, conf.reso[0], conf.reso[1]);
    conf.sizeLine = conf.reso[0] * 4;
    conf.mlx_data = mlx_get_data_addr(conf.mlx_img, &(conf.bpp), &(conf.sizeLine), &(conf.endian));
    //conf.imgpoke = (int*)mlx_get_data_addr(conf.mlx_img, &(conf.bpp), &(conf.sizeLine), &(conf.endian));
    //mlx_put_image_to_window(conf.mlx_ptr, conf.mlx_win, conf.mlx_img, 0, 0);
    while (x < conf.reso[0])
    {
        conf.cameraX = 2 * x / conf.reso[0] - 1;
        conf.rayDirX = conf.dirX + conf.planeX * conf.cameraX;
        conf.rayDirY = conf.dirY + conf.planeY * conf.cameraX;
        conf.mapX = conf.posX;
        conf.mapY = conf.posY;
        conf.deltaDistX = fabs(1 / conf.rayDirX);
        conf.deltaDistY = fabs(1 / conf.rayDirY);
        conf.hit = 0;
        if (conf.rayDirX < 0)
        {
            conf.stepX = -1;
            conf.sideDistX = (conf.posX - conf.mapX) * conf.deltaDistX;
        }
        else
        {
            conf.stepX = 1;
            conf.sideDistX = (conf.mapX + 1.0 - conf.posX) * conf.deltaDistX;
        }
        if (conf.rayDirY < 0)
        {
            conf.stepY = -1;
            conf.sideDistY = (conf.posY - conf.mapY) * conf.deltaDistY;
        }
        else
        {
            conf.stepY = 1;
            conf.sideDistY = (conf.mapY + 1.0 - conf.posY) * conf.deltaDistY;
        }
        while (conf.hit == 0)
        {
            if (conf.sideDistX < conf.sideDistY)
            {
                conf.sideDistX += conf.deltaDistX;
                conf.mapX += conf.stepX;
                conf.side = 0;
            }
            else
            {
                conf.sideDistY += conf.deltaDistY;
                conf.mapY += conf.stepY;
                conf.side = 1;
            }
            if (conf.map[conf.mapX][conf.mapY] == '1')
            {
                ft_printf("x = %d, y = %d\n", conf.mapX, conf.mapY);
                conf.hit = 1;
            }
        }
        if (conf.side == 0) 
            conf.perpWallDist = (conf.mapX - conf.posX + (1 - conf.stepX) / 2) / conf.rayDirX;
        else          
            conf.perpWallDist = (conf.mapY - conf.posY + (1 - conf.stepY) / 2) / conf.rayDirY;
        conf.lineHeight = (int)(conf.reso[1] / conf.perpWallDist);
        conf.drawStart = -(conf.lineHeight) / 2 + conf.reso[1] / 2; 
        if (conf.drawStart <  0) 
            conf.drawStart = 0;
        conf.drawEnd = conf.lineHeight / 2 + conf.reso[1] / 2;
        if (conf.drawEnd >= conf.reso[1]) 
            conf.drawEnd = conf.reso[1] - 1;
        if (conf.map[conf.mapY][conf.mapX] == '1')
            conf.color = 0xFF0000;
        int y;

        y = 0;
        while (y < conf.drawStart)
        {
            conf.color = 0x9400D3;
            mlx_pixel_put(conf.mlx_ptr, conf.mlx_win, x, y, conf.color);
            y++;
        }
        while (y < conf.drawEnd)
        {
            conf.color = 0xFF0000;
            mlx_pixel_put(conf.mlx_ptr, conf.mlx_win, x, y, conf.color);
            y++;
        }
        while (y < conf.reso[1])
        {
             conf.color = 0x000D3;
            mlx_pixel_put(conf.mlx_ptr, conf.mlx_win, x, y, conf.color);
            y++;
        }
        x++;
    }
    //mlx_put_image_to_window(conf.mlx_ptr, conf.mlx_win, conf.mlx_img, 0, 0);
    mlx_loop(conf.mlx_ptr);
    return (EXIT_SUCCESS);
}
