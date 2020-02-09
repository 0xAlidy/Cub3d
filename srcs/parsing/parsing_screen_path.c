/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing_screen_path.c                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 09:17:29 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 11:55:48 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_check_after(char *str, int i)
{
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		ft_util_path(char *line, int *i)
{
	int save;

	while (line[(*i)] && line[(*i)] == ' ')
		(*i) += 1;
	save = (*i);
	while (line[(*i)] && line[(*i)] != ' ')
		(*i) += 1;
	return (save);
}

void	ft_parsing_path(char *line, t_cube *conf, int i, int nb)
{
	int		save;
	char	*res;
	int		fd;

	save = ft_util_path(line, &i);
	res = ft_substr(line, save, i - save);
	if ((fd = open(res, 'r')) < 0)
		ft_stderr(3, conf);
	close(fd);
	if (nb == 1 && !(conf->no) && ft_check_after(line, i))
		conf->no = res;
	else if (nb == 2 && !(conf->so) && ft_check_after(line, i))
		conf->so = res;
	else if (nb == 3 && !(conf->we) && ft_check_after(line, i))
		conf->we = res;
	else if (nb == 4 && !(conf->ea) && ft_check_after(line, i))
		conf->ea = res;
	else if (nb == 5 && !(conf->s) && ft_check_after(line, i))
		conf->s = res;
	else
	{
		free(res);
		ft_stderr(3, conf);
	}
}

void	ft_test_screen(int i, char *line, t_cube *conf)
{
	int ok;
	int cpt;

	ok = 0;
	cpt = 0;
	while (line[i])
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != ' ')
			ft_stderr(2, conf);
		if (line[i] == ' ')
			ok = 1;
		else
		{
			if (ok == 1)
				cpt++;
			ok = 0;
		}
		i++;
	}
	if (cpt != 1)
		ft_stderr(2, conf);
}

void	ft_parsing_screen(char *line, t_cube *conf, int i)
{
	int	res;

	res = 0;
	while (line[i] && line[i] == ' ')
		i++;
	ft_test_screen(i, line, conf);
	if ((res = ft_atoi(line + i)) > 1 && conf->reso[0] == 0)
		conf->reso[0] = res;
	else
		ft_stderr(2, conf);
	if (conf->reso[0] > (5120 / 2))
		conf->reso[0] = (5120 / 2);
	while (line[i] && (line[i] >= '0' && line[i] <= '9'))
		i++;
	if ((res = ft_atoi(line + i)) > 1 && conf->reso[1] == 0)
		conf->reso[1] = res;
	else
		ft_stderr(2, conf);
	if (conf->reso[1] > ((2880 / 2) - 45))
		conf->reso[1] = ((2880 / 2) - 45);
}
