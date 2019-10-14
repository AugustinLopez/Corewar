/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 11:33:46 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/04 11:40:55 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	ft_is_in_base(char car, char *base)
{
	int		i;

	i = 0;
	if (car == '+' || car == '-' || car == '\0')
		return (-2);
	while (base[i] != '\0')
	{
		if (base[i] == car)
			return (i);
		i++;
	}
	return (-1);
}

long		ft_atol_base(char *str, char *base)
{
	int		i;
	long	tmp;
	int		neg;

	i = 0;
	neg = 1;
	tmp = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_is_in_base(str[i], base) >= 0)
	{
		tmp *= ft_strlen(base);
		tmp += (ft_is_in_base(str[i], base)) * neg;
		i++;
	}
	if (ft_is_in_base(str[i], base) == -1)
		return (0);
	return (tmp);
}
