/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 02:14:26 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 21:06:55 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/cub3d.h"

int 	main(int gc, char **gv)
{
    cube_t		conf;
    
    conf = ft_init_conf();
    ft_parsing_all(gc, gv, &conf);
	/*if (gc == 3)
	{
		// -save
	}*/
	int y = 0;
	int x = 0;
	while (conf.map[y])
	{
		while (conf.map[y][x])
		{
			ft_printf("%c",conf.map[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
		x = 0;
	}
	ft_game(&conf);
	/*if ((conf.mlx_ptr = mlx_init()) == NULL)
        ft_stderr(-1, &conf);
    if ((conf.mlx_win = mlx_new_window(conf.mlx_ptr, conf.reso[0], conf.reso[1], "Cub3D")) == NULL)
        ft_stderr(-1, &conf);
	conf.mlx_img = mlx_xpm_file_to_image(conf.mlx_ptr,conf.no,&conf.reso[0],&conf.reso[1]);
	mlx_put_image_to_window(conf.mlx_ptr, conf.mlx_win, conf.mlx_img, 0, 0);
	mlx_loop(conf.mlx_ptr);*/
    return (EXIT_SUCCESS);
}
