/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   cub3d.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/18 10:35:44 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/08 18:24:50 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/ft_printf.h"
#include "../minilibx/mlx.h"
# include <math.h>

typedef struct 		hf_s
{
	unsigned char	type[2];
	int 			size;
	short 			reserved1;
	short 			reserved2;
	unsigned int	offBits;
}					hf_t;

typedef struct 		hi_s
{
	unsigned int 	sizeH;
	unsigned int 	width;
	unsigned int 	height;
	short int		planes;
	short int		bitCount;
	unsigned int 	compression;
	unsigned int	sizeImage;
	unsigned int	xPelsPerMeter;
	unsigned int	yPelsPerMeter;
	unsigned int	clrUsed;
	unsigned int	clrImportant;
}					hi_t;

typedef struct		cube_s
{
	void			*mlx_ptr;
    void			*mlx_win;
	void			*mlx_img;
	void			*textNo;
	void			*textSo;
	void			*textEa;
	void			*textWe;
	void			*textSprite;
	int				*mlx_data;
	int				*dataNo;
	int				*dataSo;
	int				*dataEa;
	int				*dataWe;
	int				*dataSprite;
	int				*dataText;
    int				reso[2];
	int 			sizeLine;
	int				endian;
	int 			bpp;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				f[3];
	int				c[3];
	char			**map;
	char			*temp;
	char			ori;
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
	double			cameraX;
	double			rayDirX;
	double			rayDirY;
	int 			lenX;
	int				mapX;
	int				mapY;
	double			sideDistX;
	double			sideDistY;
	double			deltaDistX;
	double 			deltaDistY;
	int				lineHeight;
	double			perpWallDist;
	int				stepX;
	int				stepY;
	int				hit;
	int				side;
	int				drawStart;
	int				drawEnd;
	int 			color;
	int				colorF;
	int				colorC;
	int				keyDown;
	int				keyUp;
	int				keyLeft;
	int				keyRight;
	double			rotaSpeed;
	double			moveSpeed;
	int				textWidth;
	int				textHeight;
	double			wall_x;
	int				tex_x;
	int				tex_y;
}					cube_t;

void				ft_stderr(int nb, cube_t *conf);
void				ft_free_conf(cube_t *conf);
cube_t				ft_init_conf(void);
int					ft_check_after(char *str, int i);
int		            ft_parsing_arg(int gc, char **gv);
int					ft_get_id(char *str, cube_t *conf);
int					ft_parsing_map(char *line, cube_t *conf, int *check);
void				ft_get_start(cube_t *conf, char c, int x, int y);
void 				ft_parsing_screen(char *line, cube_t *conf, int i);
void				ft_parsing_color(char *line, cube_t *conf, int i, int nb);
void    			ft_parsing_path(char *line, cube_t *conf, int i, int nb);
void				ft_parsing_conf(char *line, cube_t *conf, int i);
void   				ft_parsing_all(int gc, char **gv, cube_t *conf);
int					ft_raycasting(cube_t *conf);
int					color(int r, int g, int b);
int					keyhooks(cube_t *conf);
int					ft_define_movement(int key, cube_t *conf);
int					ft_reset_movement(int key, cube_t *conf);
void    			ft_game(cube_t *conf);
int					ft_raycasting(cube_t *conf);
int					ft_close_mlx(cube_t *conf);
void				ft_init_cube(cube_t *c);
void				ft_init_raycast(int x, cube_t *conf);
void				ft_draw1(cube_t *conf);
void				ft_draw2(cube_t *conf);
void    			ft_drawText(int x, cube_t *c);
void				ft_draw3(int x, cube_t *c);
void				ft_start_rota(cube_t *conf);
void				ft_start_move(cube_t *c);
void				ft_create_bmp(cube_t *conf);

#endif