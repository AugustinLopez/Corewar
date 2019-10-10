/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islong.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 11:42:01 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/04 14:02:28 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mde-laga.h"

static int		ft_check_len(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] == '+' || str[i] == '-' || str[i] == '0')
		i++;
	while (str[i++])
		count++;
	if (count == 19)
		return (2);
	return (count > 19 ? 0 : 1);
}

int				ft_islong(char *str)
{
	long	nb;
	char	*cmp;
	int		len;

	if (!ft_str_is_numeric(str[0] == '-' || str[0] == '+' ? str + 1 : str))
		return (0);
	if (!(len = ft_check_len(str)))
		return (0);
	else if (len == 2)
	{
		nb = ft_atol(str);
		cmp = ft_ltoa(nb);
		if (ft_strcmp(cmp, str))
		{
			free(cmp);
			return (0);
		}
		free(cmp);
	}
	return (1);
}
