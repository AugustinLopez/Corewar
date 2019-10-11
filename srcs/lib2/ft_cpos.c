/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:40:50 by mde-laga          #+#    #+#             */
/*   Updated: 2019/09/19 17:45:53 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_cpos(char *str, char c)
{
	int		pos;
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	pos = ch - str;
	return (pos);
}
