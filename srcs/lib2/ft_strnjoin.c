/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 12:55:00 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/11 15:22:17 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	char	*str;
	size_t	len;

	len = ft_strlen(s1);
	if (n < len)
		len = n;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(*str) * (len + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (*s1 && i < n)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}
