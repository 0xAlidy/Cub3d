/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ray_sprite.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 14:03:45 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/14 04:09:32 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int     ft_add_lst_sprite(int x, int y, t_sprite **lst)
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

void    ft_sort_sprite(t_cube *c, t_sprite *lst)
{
    double dist;
    double dist2;
    int save;
    t_sprite *sav;

    sav = lst;
    while(lst->next)
    {
        dist = pow((c->pos_x - lst->x), 2) + pow(c->pos_y - lst->y,2);
        dist2 = pow(c->pos_x - lst->next->x,2) + pow(c->pos_y - lst->next->y,2);
        dist = sqrt(dist);
        dist2 = sqrt(dist2);
        if (dist < dist2)
        {
            save = lst->x;
            lst->x = (lst->next)->x;
            (lst->next)->x = save;
            save = lst->y;
            lst->y = (lst->next)->y;
            (lst->next)->y = save;
            lst = sav;
        }
        else
            lst = lst->next;
    }
    lst = sav;
}

void	ft_draw_sprite(t_cube *c, t_sprite *lst)
{
    t_sprite *save;
    if (lst && lst->next)
        ft_sort_sprite(c, lst);
    while (lst)
    {
        double sprite_x = lst->x - c->pos_x + 0.5;
        double sprite_y = lst->y - c->pos_y + 0.5;
        double invDet = 1.0 / (c->plane_x * c->dir_y - c->dir_x * c->plane_y);
        double transform_x = invDet * (c->dir_y * sprite_x - c->dir_x * sprite_y);
        double transform_y = invDet * (-c->plane_y * sprite_x + c->plane_x * sprite_y);
        int sprite_screen_x = (int)((c->reso[0] / 2) * (1 + transform_x / transform_y));
        int sprite_height = abs((int)(c->reso[1] / (transform_y)));
        int draw_start_y = -sprite_height / 2 + c->reso[1] / 2;
        if (draw_start_y < 0)
	    	draw_start_y = 0;
        int draw_end_y = sprite_height / 2 + c->reso[1] / 2;
        if (draw_end_y >= c->reso[1])
	    	draw_end_y = c->reso[1] - 1;
        int sprite_width = abs ((int)(c->reso[1] / (transform_y)));
        int draw_start_x = (-sprite_width / 2 + sprite_screen_x);
        if (draw_start_x < 0) 
	    	draw_start_x = 0;
        int draw_end_x = sprite_width / 2 + sprite_screen_x;
        if (draw_end_x >= c->reso[0]) 
	    	draw_end_x = c->reso[0] - 1;
	    int stripe = draw_start_x;
        while (stripe < draw_end_x)
        {
	    	int texX = (int)((256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * c->text_width / sprite_width) / 256);
	    	int y = draw_start_y;
            	while (y < draw_end_y)
             	{
              		int d = (y) * 256 - c->reso[1] * 128 + sprite_height * 128;
               		int texY = ((d * c->text_height) / sprite_height) / 256;
              		c->color = c->data_sprite[c->text_width * texY + texX];
               		if (c->color)
	    	   			c->mlx_data[y * c->reso[0] + stripe] = c->color;
	    			y++;
             	}
	    	stripe++;
        }
        save = lst;
        lst = lst->next;
        free(save);
    }
}
