/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isparam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:56:03 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/08 17:32:38 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_isreg(char *str)
{
	int		i;
	int		cmp;

	i = 0;
	if (str[i++] != 'r' || !ft_isdigit(str[i]) || !ft_isint(str + i))
		return (0);
	cmp = ft_atoi(str + i);
	if (cmp < 0 || cmp > 255)
		return (0);
	return (1);
}

int		ft_isdir(char *str)
{
	int		i;

	i = 0;
	if (str[i++] != DIRECT_CHAR)
		return (0);
	if (str[i] == LABEL_CHAR)
	{
		while (str[++i])
			if (!ft_islabchar(str[i]))
				return (0);
	}
	else if (!ft_str_is_numeric(str[i] == '-' ? str + 2 : str + 1))
		if (!(str[1] == '0' && str[2] == 'X' && ft_str_is_mxdigit(str + 3)))
			return (0);
	return (1);
}

int		ft_isind(char *str)
{
	int		i;

	i = 0;
	if (str[i] == LABEL_CHAR)
	{
		while (str[++i])
			if (!ft_islabchar(str[i]))
				return (0);
	}
	else if (!ft_str_is_numeric(str[i] == '-' ? str + 1 : str))
		if (!(str[0] == '0' && str[1] == 'X' && ft_str_is_mxdigit(str + 2)))
			return (0);
	return (1);
}

int		ft_isparam(char *str)
{
	int		ret;

	ret = 0;
	if (ft_isreg(str))
		ret = REG_CODE;
	else if (ft_isdir(str))
		ret = DIR_CODE;
	else if (ft_isind(str))
		ret = IND_CODE;
	return (ret);
}
