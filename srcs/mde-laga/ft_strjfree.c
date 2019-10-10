/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:10:12 by mde-laga          #+#    #+#             */
/*   Updated: 2019/03/01 11:18:34 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mde-laga.h"

static int	ft_free(char *s1, char *s2)
{
	if (s1 != NULL)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2 != NULL)
	{
		free(s2);
		s2 = NULL;
	}
	return (0);
}

char		*ft_strjfree(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL)
	{
		if ((str = ft_strdup(s2)) == 0)
			return (0);
		return (str);
	}
	else
	{
		if ((str = ft_strjoin(s1, s2)) == 0)
			return (0);
		ft_free(s1, s2);
		return (str);
	}
}
