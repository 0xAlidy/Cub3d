/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 02:14:26 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/04 03:22:03 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../minilibx/mlx.h"

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
    conf.mlx_data = (int *)mlx_get_data_addr(conf.mlx_img, &(conf.bpp), &(conf.sizeLine), &(conf.endian));
    //switch
    conf.mapX = conf.posX;
    conf.posX = conf.posY;
    conf.posY = conf.mapX;
    while (x < conf.reso[0])
    {
        conf.cameraX = 2 * x / (float)conf.reso[0] - 1;
        conf.rayDirX = conf.dirX + conf.planeX * conf.cameraX;
        conf.rayDirY = conf.dirY + conf.planeY * conf.cameraX;
        conf.mapX = (int)conf.posX;
        conf.mapY = (int)conf.posY;
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
                conf.hit = 1;
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
        int		initioy;
		int		mori;
		int		initio;

		mori = conf.drawEnd;
		if (mori > conf.reso[1])
			mori = conf.reso[1] - 1;
		initioy = conf.drawStart;
		if (initioy < 0)
			initioy = 0;
		initio = -1;
		while (++initio < (conf.reso[1] / 2))
			conf.mlx_data[x + (initio * conf.sizeLine / 4)] = 0xC00000AA;
		while (++initioy < mori)
			conf.mlx_data[x + (initioy * conf.sizeLine / 4)] = 0xFF0000;
		initio = mori - 1;
		while (++initio < (conf.reso[1] - 1))
			conf.mlx_data[x + (initio * conf.sizeLine / 4)] = 0xC00000AA;
        x++;
    }
    mlx_put_image_to_window(conf.mlx_ptr, conf.mlx_win, conf.mlx_img, 0, 0);
    mlx_loop(conf.mlx_ptr);
    return (EXIT_SUCCESS);
}
