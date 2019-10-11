/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getheader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:46 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/09 17:17:12 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_glueline(t_struct *s)
{
	char	*glue;
	int		status;
	int		i;

	status = 0;
	i = -1;
	while (status != 1 && s->rd->data[++i])
		s->rd->data[i] == '"' ? status++ : 1;
	if (!status)
		ft_error(s, INFO_ERR, 0);
	while (status != 2 && s->rd)
	{
		while (status != 2 && s->rd->data[++i])
			s->rd->data[i] == '"' ? status++ : 1;
		if (status != 2)
		{
			if (!s->rd->next)
				ft_error(s, INFO_ERR, 0);
			s->rd->data = ft_strjfree(s->rd->data, ft_strdup("\n"));
			glue = ft_strjoin(s->rd->data, s->rd->next->data);
			ft_next_rd(s);
			free(s->rd->data);
			s->rd->data = glue;
		}
	}
}

static int	ft_get_i(t_struct *s, int dir)
{
	int		i;

	i = 0;
	while (ft_isblank(s->rd->data[i]))
		i++;
	i += dir == 1 ? 5 : 8;
	while (ft_isblank(s->rd->data[i]))
		i++;
	return (i + 1);
}

static void	ft_getinfo(t_struct *s, int dir)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = ft_get_i(s, dir);
	j = 0;
	while (s->rd->data[i + j] && s->rd->data[i + j] != '"')
		j++;
	k = j;
	if (j > (dir == 1 ? PROG_NAME_LENGTH : COMMENT_LENGTH))
		ft_error(s, dir == 1 ? LONG_N : LONG_C, 0);
	while (s->rd->data[i + ++k])
		if (!ft_isblank(s->rd->data[i + k]) && s->rd->data[i + k] != COM_CHAR)
			ft_error(s, INFO_ERR, 0);
		else if (s->rd->data[i + k] == COM_CHAR)
			break ;
	str = ft_strsub(s->rd->data, i, j);
	if (str)
		ft_memcpy(dir == 1 ? s->header.prog_name : s->header.comment
			, str, ft_strlen(str));
	free(str);
	ft_next_rd(s);
}

void		ft_getheader(t_struct *s)
{
	int			dir;
	int			dup;

	dup = 0;
	while (dup != 3)
	{
		while (s->rd && ft_isskip(s->rd->data))
			ft_next_rd(s);
		dir = ft_isinfo(s->rd->data);
		if ((dir == 1 && dup != 1) || (dir == 2 && dup != 2))
		{
			ft_glueline(s);
			ft_getinfo(s, dir);
			dup += dir;
		}
		else if (!dir)
			ft_error(s, NOT_NC, 0);
		else
			ft_error(s, dir == 1 ? DUP_N : DUP_C, 0);
	}
}
