/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube_bmp.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/08 16:58:08 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 21:38:32 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_fill_bmp(int fd, t_himg bih, t_cube *conf)
{
	unsigned char	color[3];
	int				x;
	int				y;
	int				pix;

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

void	ft_init_bmp(char *filename, t_cube *conf)
{
	int			fd;
	t_hfile		bfh;
	t_himg		bih;

	bfh.type[0] = 'B';
	bfh.type[1] = 'M';
	bfh.size = conf->reso[0] * conf->reso[1] * 4 + 54;
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.off_bits = 0;
	bih.size_h = sizeof(bih);
	bih.width = conf->reso[0];
	bih.height = conf->reso[1];
	bih.planes = 1;
	bih.bit_count = 24;
	bih.compression = 0;
	bih.size_img = conf->reso[0] * conf->reso[1] * 4 + 54;
	bih.x_ppm = 2;
	bih.y_ppm = 2;
	bih.clr_used = 0;
	bih.clr_important = 0;
	fd = open(filename, O_RDWR | O_CREAT, 0777);
	write(fd, &bfh, 14);
	ft_fill_bmp(fd, bih, conf);
	close(fd);
}

void	ft_create_bmp(t_cube *conf)
{
	int			x;
	t_sprite 	*lst;

	x = 0;
	lst = 0;
	ft_init_cube(conf);
	ft_start_rota(conf);
	ft_start_move(conf);
	while (x < conf->reso[0])
	{
		ft_init_raycast(x, conf);
		ft_draw1(conf);
		ft_draw2(conf, &lst);
		ft_draw3(x, conf);
		x++;
	}
	ft_draw_sprite(conf, lst);
	ft_init_bmp("cube.bmp", conf);
}
