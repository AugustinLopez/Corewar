/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_mxdigit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 12:07:38 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/07 14:43:46 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_str_is_mxdigit(char *str)
{
	int i;

	i = -1;
	if (!str[0])
		return (0);
	while (str[++i])
		if (ft_ismxdigit(str[i]) == 0)
			return (0);
	return (1);
}
