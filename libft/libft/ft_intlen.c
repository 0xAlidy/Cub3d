/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_intlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/12/07 03:14:43 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2019/12/10 07:47:49 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int nb)
{
	int		res;
	long	temp;

	res = 0;
	temp = nb;
	if (temp <= 0)
	{
		temp = temp * -1;
		res = 1;
	}
	while (temp > 0)
	{
		temp = temp / 10;
		res++;
	}
	return (res);
}
