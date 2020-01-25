#include "../include/cub3d.h"
#include "../minilibx/mlx.h"

int main(int gc, char **gv)
{
    data_t		data;
    cube_t		conf;	

    conf = ft_init_conf();
    ft_parsing_all(gc, gv, &conf);
    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, conf.reso[0], conf.reso[1], "Hello world")) == NULL)
        return (EXIT_FAILURE);
    mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
