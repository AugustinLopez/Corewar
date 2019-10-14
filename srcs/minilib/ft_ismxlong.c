/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismxlong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:46:09 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/04 14:02:44 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_check_len(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] == '0')
		i++;
	while (str[i++])
		count++;
	if (count == 16)
		return (2);
	return (count > 16 ? 0 : 1);
}

int				ft_ismxlong(char *str)
{
	int		i;
	int		len;

	i = -1;
	while (str[++i])
		if (!ft_ismxdigit(str[i]))
			return (0);
	if (!(len = ft_check_len(str)))
		return (0);
	else if (len == 2)
	{
		i = 0;
		while (str[i] == '0')
			i++;
		if (str[i] > '7')
			return (0);
	}
	return (1);
}
