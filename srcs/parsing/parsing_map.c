/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing_map.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/24 09:20:43 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2020/01/25 13:12:36 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int		ft_check_ori(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int		ft_parsing_m(cube_t *conf, char *line, int *check)
{
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = 0;
	while (line[i])
	{
		if ((line[i] >= '0' && line[i] <= '2'))
		{
			len++;
			i++;
		}
		else if (ft_check_ori(line[i]) && (*check) == 0)
		{
			(*check) = 1;
			i++;
		}
		else if (line[i] == ' ')
			i++;
		else
			ft_stderr(5, conf);
	}
	return (len);
}

int		ft_parsing_map(char *line, cube_t *conf, int *check)
{
	int		i;
	int		len;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if ((len = ft_parsing_m(conf, line, check)) == 0)
		return (0);
	if (!(str = malloc(len * sizeof(char))))
		ft_stderr(-1, conf);
	while (line[i])
	{
		if (line[i] != ' ')
		{
			str[j] = line[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	conf->temp = ft_strjoin_free(conf->temp, str, 3);
	conf->temp = ft_strjoin_free(conf->temp, "\n", 1);
	return (1);
}
