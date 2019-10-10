/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:24:01 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/04 11:38:06 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mde-laga.h"

char			*ft_lutoa_base(uint64_t value, int base, int cas)
{
	int			i;
	uint64_t	tmp;
	char		*str;

	i = 0;
	if (value == 0)
		i = 1;
	tmp = value;
	while (tmp && ++i)
		tmp = tmp / base;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	tmp = value;
	while (i--)
	{
		str[i] = (tmp % base < 10 ? tmp % base + '0' :
				(tmp % base - 10 + cas));
		tmp = tmp / base;
	}
	return (str);
}
