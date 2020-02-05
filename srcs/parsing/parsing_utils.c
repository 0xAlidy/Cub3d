/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing_utils.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 09:13:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 15:35:54 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	cube_t	res;

 	res.mlx_ptr= 0;
    res.mlx_win = 0;
	res.mlx_img = 0;
	res.mlx_data = 0;
	res.sizeLine = 0;
	res.endian = 1;
	res.no = NULL;
	res.so = NULL;
	res.we = NULL;
	res.ea = NULL;
	res.s = NULL;
	res.f[0] = -1;
	res.f[1] = -1;
	res.f[2] = -1;
	res.c[0] = -1;
	res.c[1] = -1;
	res.c[2] = -1;
	res.map = NULL;
	res.temp = NULL;
	res.dirX = 0;
	res.dirY = -1;
	res.planeX = 0.66;
	res.planeY = 0;
	res.time = 0;
	res.oldtime = 0;
	res.cameraX = 0;
	res.rayDirX = 0;
	res.rayDirY = 0;
	res.mapX = 0;
	res.mapY = 0;
	res.sideDistX = 0;
	res.sideDistY = 0;
	res.deltaDistX = 0;
	res.deltaDistY = 0;
	res.lineHeight = 0;
	res.bpp = 32;
	res.hit = 0;
	res.color = 0;
	res.perpWallDist = 0;
	res.rotaSpeed = 0.06;
	res.moveSpeed = 0.06;
	return (res);
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
