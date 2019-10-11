/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joincstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:59:49 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/07 17:02:44 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*ft_joincstr(char c, char const *s2)
{
	int		i;
	char	*str;

	if (!c || !s2)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(*str) * (ft_strlen(s2) + 2))))
		return (NULL);
	i = -1;
	str[++i] = c;
	while (*s2)
		str[++i] = *s2++;
	str[++i] = '\0';
	return (str);
}
