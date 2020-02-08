/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 02:14:26 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 15:58:32 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_img(int fd, hi_t bih, cube_t *conf)
{
	int				x;
	int				y;
	int				pix;
	unsigned char	color[3];

	write(fd, &bih, sizeof(bih));
	y = conf->reso[1] - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < conf->reso[0])
		{
			pix = conf->mlx_data[x + y * conf->reso[0]];
			color[0] = pix % 256;
			pix /= 256;
			color[1] = pix % 256;
			pix /= 256;
			color[2] = pix % 256;
			write(fd, &color, sizeof(color));
			x++;
		}
		y--;
	}
}

void	save_img(const char *filename, cube_t *conf)
{
	int			fd;
	hf_t		bfh;
	hi_t		bih;

	bfh.type[0] = 'B';
	bfh.type[1] = 'M';
	bfh.size = conf->reso[0] * conf->reso[1] * 4 + 54;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.offBits = 0;
	bih.sizeH = sizeof(bih);
	bih.width = conf->reso[0];
	bih.height = conf->reso[1];
	bih.planes = 1;
	bih.bitCount = 24;
	bih.compression = 0;
	bih.sizeImage = conf->reso[0] * conf->reso[1] * 4 + 54;
	bih.xPelsPerMeter = 2;
	bih.yPelsPerMeter = 2;
	bih.clrUsed = 0;
	bih.clrImportant = 0;
	close(open(filename, O_WRONLY | O_CREAT, 0777));
	fd = open(filename, O_RDWR);
	write(fd, &bfh, 14);
	fill_img(fd, bih, conf);
	close(fd);
}

int 	main(int gc, char **gv)
{
    cube_t		conf;
	int			x;
    
	x = 0;
    conf = ft_init_conf();
    ft_parsing_all(gc, gv, &conf);
	if (gc == 3)
	{
		ft_init_cube(&conf);
		ft_startRota(&conf);
		ft_startMove(&conf);
		while (x < conf.reso[0])
    	{
        	ft_initRaycast(x, &conf);
			ft_draw1(&conf);
			ft_draw2(&conf);
			ft_draw3(x, &conf);
        	x++;
    	}
		save_img("cube.bmp", &conf);
	}
	else
		ft_game(&conf);
    return (EXIT_SUCCESS);
}
