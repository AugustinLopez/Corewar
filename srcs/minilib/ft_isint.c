/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 11:17:24 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/04 14:02:16 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_check_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] == '+' || str[i] == '-' || str[i] == '0')
		i++;
	while (str[i++])
		count++;
	return (count > 10 ? 0 : 1);
}

int				ft_isint(char *str)
{
	if (!ft_str_is_numeric(str[0] == '-' || str[0] == '+' ? str + 1 : str))
		return (0);
	if (!ft_check_len(str))
		return (0);
	if (ft_atoi(str) != ft_atol(str))
		return (0);
	return (1);
}
