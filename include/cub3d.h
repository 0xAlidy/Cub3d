/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 10:35:44 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/25 11:31:01 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/ft_printf.h"
# include <math.h>

typedef struct		data_s
{
    void			*mlx_ptr;
    void			*mlx_win;
}                   data_t;

typedef struct		cube_s
{
    int				reso[2];
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				f[3];
	int				c[3];
	char			**map;
	char			*temp;
}					cube_t;

void				ft_stderr(int nb, cube_t *conf);
cube_t				ft_init_conf(void);
int					ft_check_after(char *str, int i);
int		            ft_parsing_arg(int gc, char **gv);
int					ft_get_id(char *str, cube_t *conf);
int					ft_parsing_map(char *line, cube_t *conf, int *check);
void 				ft_parsing_screen(char *line, cube_t *conf, int i);
void				ft_parsing_color(char *line, cube_t *conf, int i, int nb);
void    			ft_parsing_path(char *line, cube_t *conf, int i, int nb);
void				ft_parsing_conf(char *line, cube_t *conf, int i);
void   				ft_parsing_all(int gc, char **gv, cube_t *conf);

#endif