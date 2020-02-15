/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:25:49 by alidy             #+#    #+#             */
/*   Updated: 2020/02/15 20:30:45 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		ft_close_mlx(t_cube *conf)
{
	if (conf->text_s)
		mlx_destroy_image(conf->mlx_ptr, conf->text_s);
	if (conf->text_no)
		mlx_destroy_image(conf->mlx_ptr, conf->text_no);
	if (conf->text_so)
		mlx_destroy_image(conf->mlx_ptr, conf->text_so);
	if (conf->text_ea)
		mlx_destroy_image(conf->mlx_ptr, conf->text_ea);
	if (conf->text_we)
		mlx_destroy_image(conf->mlx_ptr, conf->text_we);
	if (conf->mlx_img)
		mlx_destroy_image(conf->mlx_ptr, conf->mlx_img);
	if (conf->mlx_win)
		mlx_destroy_window(conf->mlx_ptr, conf->mlx_win);
	ft_free_conf(conf);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	ft_free_conf(t_cube *conf)
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

void	ft_stderr(int nb, t_cube *conf)
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
