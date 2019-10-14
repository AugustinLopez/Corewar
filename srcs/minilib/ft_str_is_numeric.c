/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:36:48 by mde-laga          #+#    #+#             */
/*   Updated: 2019/04/30 15:40:49 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_str_is_numeric(char *str)
{
	int i;

	i = -1;
	if (!str[0])
		return (0);
	while (str[++i])
		if (ft_isdigit(str[i]) == 0)
			return (0);
	return (1);
}
