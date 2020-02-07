/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cube.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 02:14:26 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 16:37:54 by alidy       ###    #+. /#+    ###.fr     */
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
	ft_game(&conf);
    return (EXIT_SUCCESS);
}
