/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 14:12:11 by mde-laga          #+#    #+#             */
/*   Updated: 2019/09/22 11:58:14 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mde-laga.h"

char	*ft_strtrimfree(char *s)
{
	int		i;
	int		len;
	char	*s2;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	while (s[len - 1] == ' ' || s[len - 1] == '\n' || s[len - 1] == '\t')
		len--;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		i++;
		len--;
	}
	if (len < 0)
		len = 0;
	s2 = ft_strsub(s, i, len);
	free(s);
	return (s2);
}
