/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 10:32:50 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/09 11:30:21 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mde-laga.h"

char	*ft_strsubfree(char *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	if (!s || !len)
		return (NULL);
	if (!(s2 = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = -1;
	while (++i < len)
		s2[i] = s[start + i];
	s2[i] = '\0';
	free(s);
	return (s2);
}
