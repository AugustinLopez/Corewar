/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 09:41:56 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/11 15:31:28 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_nc_form(t_struct *s, char *str, int fd)
{
	int		i;

	i = 0;
	while (ft_isblank(str[i]))
		i++;
	if (str[i] != '.')
	{
		free(str);
		ft_gnl(-1, NULL, 0);
		close(fd);
		ft_error(s, NOT_NC, 0);
	}
}

static void	*ft_gnlerr(t_struct *s)
{
	s->rderr = 1;
	ft_gnl(-1, NULL, 0);
	return (NULL);
}

t_rd		*ft_read(t_struct *s, int fd, int beg)
{
	t_rd	*rd;
	char	*str;
	int		ret;

	rd = NULL;
	if ((ret = ft_gnl(fd, &str, 0)) > 0)
	{
		if (beg && ft_isskip(str))
		{
			free(str);
			s->line++;
			return (ft_read(s, fd, beg));
		}
		else if (beg && (beg = 0))
			ft_nc_form(s, str, fd);
		if (!(rd = (t_rd*)malloc(sizeof(t_rd))))
			return (NULL);
		rd->data = str;
		rd->next = ft_read(s, fd, beg);
	}
	if (ret == -1)
		return (ft_gnlerr(s));
	return (rd);
}
