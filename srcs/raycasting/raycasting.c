/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 17:06:49 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 12:08:33 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_draw1(t_cube *conf)
{
	if (conf->rdir_x < 0)
	{
		conf->step_x = -1;
		conf->sdist_x = (conf->pos_x - conf->map_x) * conf->ddist_x;
	}
	else
	{
		conf->step_x = 1;
		conf->sdist_x = (conf->map_x + 1.0 - conf->pos_x) * conf->ddist_x;
	}
	if (conf->rdir_y < 0)
	{
		conf->step_y = -1;
		conf->sdist_y = (conf->pos_y - conf->map_y) * conf->ddist_y;
	}
	else
	{
		conf->step_y = 1;
		conf->sdist_y = (conf->map_y + 1.0 - conf->pos_y) * conf->ddist_y;
	}
}

void	ft_draw2(t_cube *conf)
{
	while (conf->hit == 0)
	{
		if (conf->sdist_x < conf->sdist_y)
		{
			conf->sdist_x += conf->ddist_x;
			conf->map_x += conf->step_x;
			conf->side = 0;
		}
		else
		{
			conf->sdist_y += conf->ddist_y;
			conf->map_y += conf->step_y;
			conf->side = 2;
		}
		if (conf->map[conf->map_y][conf->map_x] == '1')
		{
			conf->hit = 1;
			if (conf->side == 0 && conf->map_x < conf->pos_x)
				conf->side = 1;
			else if (conf->side != 0 && conf->map_y < conf->pos_y)
				conf->side = 3;
		}
	}
}

void	ft_choose_text(t_cube *c)
{
	if (c->side == 3)
		c->data_text = c->data_no;
	else if (c->side == 2)
		c->data_text = c->data_so;
	else if (c->side == 1)
		c->data_text = c->data_we;
	else
		c->data_text = c->data_ea;
}

void	ft_draw_text(int x, t_cube *c)
{
	double	tex_pos;
	double	step;
	int		y;

	y = c->draw_s - 1;
	if (c->side == 0 || c->side == 1)
		c->wall_x = c->pos_y + c->pwd * c->rdir_y;
	else
		c->wall_x = c->pos_x + c->pwd * c->rdir_x;
	c->wall_x -= floor((c->wall_x));
	c->tex_x = c->wall_x * (double)c->text_width;
	if ((c->side == 0 || c->side == 1) && c->rdir_x > 0)
		c->tex_x = c->text_width - c->tex_x - 1;
	if ((c->side == 2 || c->side == 3) && c->rdir_y < 0)
		c->tex_x = c->text_width - c->tex_x - 1;
	step = 1.0 * c->text_height / c->line_h;
	tex_pos = (c->draw_s - c->reso[1] / 2 + c->line_h / 2) * step;
	ft_choose_text(c);
	while (++y < c->draw_e)
	{
		c->tex_y = (int)tex_pos;
		tex_pos += step;
		c->color = c->data_text[c->text_height * c->tex_y + c->tex_x];
		c->mlx_data[y * c->reso[0] + x] = c->color;
	}
}

void	ft_draw3(int x, t_cube *c)
{
	int i;

	i = 0;
	if (c->side == 0 || c->side == 1)
		c->pwd = (c->map_x - c->pos_x + (1 - c->step_x) / 2) / c->rdir_x;
	else
		c->pwd = (c->map_y - c->pos_y + (1 - c->step_y) / 2) / c->rdir_y;
	c->line_h = (long int)(c->reso[1] / c->pwd);
	c->draw_s = -c->line_h / 2 + c->reso[1] / 2;
	if (c->draw_s < 0)
		c->draw_s = 0;
	c->draw_e = c->line_h / 2 + c->reso[1] / 2;
	if (c->draw_e >= c->reso[1])
		c->draw_e = c->reso[1] - 1;
	while (i < c->draw_s)
	{
		c->mlx_data[i * c->reso[0] + x] = c->color_c;
		i++;
	}
	ft_draw_text(x, c);
	i = c->draw_e - 1;
	while (++i < c->reso[1] - 1)
		c->mlx_data[i * c->reso[0] + x] = c->color_f;
}
