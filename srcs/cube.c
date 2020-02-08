/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/08 16:52:54 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 18:30:39 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_game(cube_t *conf)
{
	ft_init_cube(conf);
	if ((conf->mlx_win = mlx_new_window(conf->mlx_ptr,
	conf->reso[0], conf->reso[1], "Cub3D")) == NULL)
		ft_close_mlx(conf);
	ft_start_rota(conf);
	ft_start_move(conf);
	mlx_loop_hook(conf->mlx_ptr, ft_raycasting, conf);
	mlx_hook(conf->mlx_win, 2, 0, ft_define_movement, conf);
	mlx_hook(conf->mlx_win, 3, 0, ft_reset_movement, conf);
	mlx_hook(conf->mlx_win, 17, 0, ft_close_mlx, conf);
	mlx_loop(conf->mlx_ptr);
}

int		ft_raycasting(cube_t *conf)
{
	int x;

	x = 0;
	mlx_clear_window(conf->mlx_ptr, conf->mlx_win);
	while (x < conf->reso[0])
	{
		ft_init_raycast(x, conf);
		ft_draw1(conf);
		ft_draw2(conf);
		ft_draw3(x, conf);
		x++;
	}
	keyhooks(conf);
	mlx_put_image_to_window(conf->mlx_ptr, conf->mlx_win, conf->mlx_img, 0, 0);
	return (0);
}

int		main(int gc, char **gv)
{
	cube_t		conf;

	conf = ft_init_conf();
	ft_parsing_all(gc, gv, &conf);
	if (gc == 3)
		ft_create_bmp(&conf);
	else
		ft_game(&conf);
	return (EXIT_SUCCESS);
}
