/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 09:13:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 21:50:56 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_raycast(int x, t_cube *conf)
{
	conf->hit = 0;
	conf->camera = 2 * x / (double)conf->reso[0] - 1;
	conf->rdir_x = conf->dir_x + conf->plane_x * conf->camera;
	conf->rdir_y = conf->dir_y + conf->plane_y * conf->camera;
	conf->map_x = (int)conf->pos_x;
	conf->map_y = (int)conf->pos_y;
	conf->ddist_x = fabs(1 / conf->rdir_x);
	conf->ddist_y = fabs(1 / conf->rdir_y);
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

void	ft_init_text(t_cube *c)
{
	c->text_so = mlx_xpm_file_to_image(c->mlx_ptr,
		c->so, &(c->text_width), &(c->text_height));
	c->text_no = mlx_xpm_file_to_image(c->mlx_ptr,
		c->no, &(c->text_width), &(c->text_height));
	c->text_ea = mlx_xpm_file_to_image(c->mlx_ptr,
		c->ea, &(c->text_width), &(c->text_height));
	c->text_we = mlx_xpm_file_to_image(c->mlx_ptr,
		c->we, &(c->text_width), &(c->text_height));
	c->text_sprite = mlx_xpm_file_to_image(c->mlx_ptr,
		c->s, &(c->text_width), &(c->text_height));	
	c->data_sprite = (int *)mlx_get_data_addr(c->text_sprite,
		&(c->bpp), &(c->size_line), &(c->endian));
	c->data_no = (int *)mlx_get_data_addr(c->text_no,
		&(c->bpp), &(c->size_line), &(c->endian));
	c->data_so = (int *)mlx_get_data_addr(c->text_so,
		&(c->bpp), &(c->size_line), &(c->endian));
	c->data_ea = (int *)mlx_get_data_addr(c->text_ea,
		&(c->bpp), &(c->size_line), &(c->endian));
	c->data_we = (int *)mlx_get_data_addr(c->text_we,
		&(c->bpp), &(c->size_line), &(c->endian));
}

void	ft_init_cube(t_cube *c)
{
	if ((c->mlx_ptr = mlx_init()) == NULL)
		ft_stderr(-1, c);
	c->mlx_img = mlx_new_image(c->mlx_ptr, c->reso[0], c->reso[1]);
	c->mlx_win = 0;
	c->size_line = c->reso[0] * 4;
	c->mlx_data = (int *)mlx_get_data_addr(c->mlx_img,
		&(c->bpp), &(c->size_line), &(c->endian));
	c->color_f = color(c->f[0], c->f[1], c->f[2]);
	c->color_c = color(c->c[0], c->c[1], c->c[2]);
	ft_init_text(c);
}

t_cube	ft_init_conf(void)
{
	t_cube	conf;

	conf.f[0] = -1;
	conf.f[1] = -1;
	conf.f[2] = -1;
	conf.c[0] = -1;
	conf.c[1] = -1;
	conf.c[2] = -1;
	conf.endian = 1;
	conf.dir_x = 0;
	conf.dir_y = -1;
	conf.plane_x = 0.66;
	conf.plane_y = 0;
	conf.bpp = 32;
	conf.rota_s = 0.03;
	conf.move_s = 0.03;
	conf.text_width = 400;
	conf.text_height = 400;
	return (conf);
}
