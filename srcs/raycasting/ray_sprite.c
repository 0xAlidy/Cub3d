/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:10:00 by alidy             #+#    #+#             */
/*   Updated: 2020/02/14 20:17:48 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_add_lst_sprite(int x, int y, t_sprite **lst)
{
	t_sprite *new;
	t_sprite *list;

	new = 0;
	list = *lst;
	if (!list)
		*lst = 0;
	else
	{
		while (list)
		{
			if (list->x == x && list->y == y)
				return (1);
			list = list->next;
		}
	}
	if (!(new = malloc(sizeof(t_sprite))))
		return (0);
	new->x = x;
	new->y = y;
	new->next = *lst;
	*lst = new;
	return (1);
}

void	ft_sort_sprite(t_cube *c, t_sprite *lst)
{
	double	dist;
	double	dist2;
	int		save;

	c->save = lst;
	while (lst->next)
	{
		dist = sqrt(pow((c->pos_x - lst->x), 2)
			+ pow(c->pos_y - lst->y, 2));
		dist2 = sqrt(pow(c->pos_x - lst->next->x, 2)
			+ pow(c->pos_y - lst->next->y, 2));
		if (dist < dist2)
		{
			save = lst->x;
			lst->x = (lst->next)->x;
			(lst->next)->x = save;
			save = lst->y;
			lst->y = (lst->next)->y;
			(lst->next)->y = save;
			lst = c->save;
		}
		else
			lst = lst->next;
	}
	lst = c->save;
}

void	ft_init_sprite(t_cube *c, t_sprite *lst)
{
	c->s_x = lst->x - c->pos_x + 0.5;
	c->s_y = lst->y - c->pos_y + 0.5;
	c->inv_det = 1.0 / (c->plane_x * c->dir_y - c->dir_x * c->plane_y);
	c->tsf_x = c->inv_det * (c->dir_y * c->s_x - c->dir_x * c->s_y);
	c->tsf_y = c->inv_det * (-c->plane_y * c->s_x + c->plane_x * c->s_y);
	c->s_screen_x = (int)((c->reso[0] / 2) * (1 + c->tsf_x / c->tsf_y));
	c->s_height = abs((int)(c->reso[1] / (c->tsf_y)));
	c->s_width = abs((int)(c->reso[1] / (c->tsf_y)));
	c->draw_s_y = -c->s_height / 2 + c->reso[1] / 2;
	c->draw_e_y = c->s_height / 2 + c->reso[1] / 2;
	c->draw_s_x = (-c->s_width / 2 + c->s_screen_x);
	c->draw_e_x = c->s_width / 2 + c->s_screen_x;
	if (c->draw_s_y < 0)
		c->draw_s_y = 0;
	if (c->draw_e_y >= c->reso[1])
		c->draw_e_y = c->reso[1] - 1;
	if (c->draw_s_x < 0)
		c->draw_s_x = 0;
	if (c->draw_e_x >= c->reso[0])
		c->draw_e_x = c->reso[0] - 1;
}

void	ft_draw2_sprite(t_cube *c, double *buf)
{
	int x;
	int	y;
	int	d;

	x = c->draw_s_x;
	while (x < c->draw_e_x)
	{
		c->s_tex_x = (int)((x - (-c->s_width / 2 + c->s_screen_x))
			* c->text_width / c->s_width);
		y = c->draw_s_y;
		if (c->tsf_y > 0 && x > 0 && x < c->reso[0] && c->tsf_y < buf[x])
			while (y < c->draw_e_y)
			{
				d = (y) * 256 - c->reso[1] * 128 + c->s_height * 128;
				c->s_tex_y = ((d * c->text_height) / c->s_height) / 256;
				c->color = c->data_sprite[c->text_width * c->s_tex_y + c->s_tex_x];
				if (c->color)
					c->mlx_data[y * c->reso[0] + x] = c->color;
				y++;
			}
		x++;
	}
}

void	ft_draw_sprite(t_cube *c, t_sprite *lst, double *buf)
{
	t_sprite *save;

	if (lst && lst->next)
		ft_sort_sprite(c, lst);
	while (lst)
	{
		ft_init_sprite(c, lst);
		ft_draw2_sprite(c, buf);
		save = lst;
		lst = lst->next;
		free(save);
	}
}
