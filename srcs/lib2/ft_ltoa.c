/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 13:23:45 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/04 11:19:43 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_len(int64_t nb)
{
	int len;

	len = 0;
	if (nb < 0)
		len++;
	while (nb / 10 && (nb /= 10))
		len++;
	return (len + 1);
}

static void		ft_recur(char *str, int64_t nb, int i)
{
	int neg;

	neg = (nb < 0 ? -1 : 1);
	if (nb / 10)
		ft_recur(str, nb / 10, i - 1);
	str[i] = nb % 10 * neg + '0';
}

char			*ft_ltoa(int64_t nb)
{
	char	*str;
	int		i;

	i = ft_len(nb);
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	str[i] = '\0';
	if (nb < 0)
		str[0] = '-';
	ft_recur(str, nb, i - 1);
	return (str);
}
