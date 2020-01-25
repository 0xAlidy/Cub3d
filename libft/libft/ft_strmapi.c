/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmapi.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: alidy <alidy@student.le-101.fr>            +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/12 10:21:59 by alidy        #+#   ##    ##    #+#       */
/*   Updated: 2019/10/18 11:56:14 by alidy       ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	unsigned int	size;

	if (s)
	{
		i = 0;
		size = ft_strlen(s);
		if ((str = malloc(sizeof(char) * (size + 1))) == NULL)
			return (0);
		while (i < size)
		{
			str[i] = (*f)(i, s[i]);
			i++;
		}
		str[i] = 0;
	}
	else
		str = 0;
	return (str);
}
