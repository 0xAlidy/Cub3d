/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube_utils.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 09:13:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 15:14:02 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_closeWin(cube_t *conf)
{
	mlx_destroy_image (conf->mlx_ptr, conf->textNo);
	mlx_destroy_image (conf->mlx_ptr, conf->textSo);
	mlx_destroy_image (conf->mlx_ptr, conf->textEa);
	mlx_destroy_image (conf->mlx_ptr, conf->textWe);
	mlx_destroy_image (conf->mlx_ptr, conf->mlx_img);
	mlx_destroy_window(conf->mlx_ptr, conf->mlx_win);
	ft_free_conf(conf);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	ft_free_conf(cube_t *conf)
{
	int i;

	i = 0;
	if (conf->no)
		free(conf->no);
	if (conf->so)
		free(conf->so);
	if (conf->we)
		free(conf->we);
	if (conf->ea)
		free(conf->ea);
	if (conf->s)
		free(conf->s);
	if (conf->temp)
		free(conf->temp);
	if (conf->map)
	{
		while (conf->map[i])
		{
			free(conf->map[i]);
			i++;
		}
		free(conf->map);
	}
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

void	ft_stderr(int nb, cube_t *conf)
{
	if (nb == 0)
		ft_printf("Error\n__ERROR__ARG__\n");
	else if (nb == 1)
		ft_printf("Error\n__ERROR__CONF__\n");
	else if (nb == 2)
		ft_printf("Error\n__ERROR__RESOLUTION__\n");
	else if (nb == 3)
		ft_printf("Error\n__ERROR__TEXTURE__\n");
	else if (nb == 4)
		ft_printf("Error\n__ERROR__COLOR__\n");
	else if (nb == 5)
		ft_printf("Error\n__ERROR__MAP__\n");
	else
		ft_printf("Error\n");
	if (conf)
		ft_free_conf(conf);
	exit(EXIT_FAILURE);
}
