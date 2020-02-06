/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_cube.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:35:16 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:47:56 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_closeWin(cube_t *conf)
{
	mlx_destroy_window(conf->mlx_ptr, conf->mlx_win);
	ft_free_conf(conf);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

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

void    ft_game(cube_t *conf)
{
    if ((conf->mlx_ptr = mlx_init()) == NULL)
        ft_stderr(-1, conf);
    if ((conf->mlx_win = mlx_new_window(conf->mlx_ptr, conf->reso[0], conf->reso[1], "Cub3D")) == NULL)
        ft_stderr(-1, conf);
    conf->mlx_img = mlx_new_image(conf->mlx_ptr, conf->reso[0], conf->reso[1]);
    conf->sizeLine = conf->reso[0] * 4;
    conf->mlx_data = (int *)mlx_get_data_addr(conf->mlx_img, &(conf->bpp), &(conf->sizeLine), &(conf->endian));
    mlx_loop_hook(conf->mlx_ptr, ft_raycasting, conf);
	mlx_hook(conf->mlx_win, 2, 0, ft_defineMovement, conf);
	mlx_hook(conf->mlx_win, 3, 0, ft_resetMovement, conf);
	mlx_hook(conf->mlx_win, 17, 0, ft_closeWin, conf);
    mlx_loop(conf->mlx_ptr);
}
