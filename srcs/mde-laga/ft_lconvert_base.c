/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lconvert_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 14:02:05 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/04 14:02:06 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mde-laga.h"

static char	*ft_ltoa_base(long nbr, char *base, char *str, int size)
{
	int		i;
	long	div;

	i = 0;
	div = 1;
	size -= 1;
	if (nbr < 0)
	{
		nbr *= -1;
		str[i++] = '-';
	}
	while (size > 0)
	{
		div *= ft_strlen(base);
		size--;
	}
	while (div > 0)
	{
		str[i] = base[nbr / div];
		i++;
		nbr %= div;
		div /= ft_strlen(base);
	}
	str[i] = '\0';
	return (str);
}

char		*ft_lconvert_base(char *nbr, char *base_from, char *base_to)
{
	long	nbrt[2];
	char	*str;
	int		neg;
	int		i;

	neg = 0;
	i = 0;
	nbrt[0] = ft_atol_base(nbr, base_from);
	nbrt[1] = nbrt[0];
	if (nbrt[0] < 0)
		neg = 1;
	if (nbrt[0] == 0)
	{
		str = ft_strnew(2);
		str[0] = base_to[0];
		return (str);
	}
	while (nbrt[1] != 0)
	{
		nbrt[1] /= ft_strlen(base_to);
		i++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (i + 1 + neg))))
		return (NULL);
	return (ft_ltoa_base(nbrt[0], base_to, str, i));
}
