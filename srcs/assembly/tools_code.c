/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:40 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/11 13:52:16 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_paramcom(char *str)
{
	int		c;

	if ((c = ft_cpos(str, COM_CHAR)) < 0)
		return (str);
	else
		return (ft_strsubfree(str, 0, c));
}

char		**ft_getparam(t_struct *s, int i)
{
	char	**param;
	char	*tmp;

	s->rd->data = ft_paramcom(s->rd->data);
	tmp = ft_strtrim(s->rd->data + i);
	if (tmp[0] == ',' || tmp[ft_strlen(tmp) - 1] == ',')
	{
		free(tmp);
		ft_error(s, "Test", 0);
	}
	free(tmp);
	param = ft_strsplit(s->rd->data + i, SEPARATOR_CHAR);
	return (param);
}

static int	ft_checkocp(int op, int ocp)
{
	int		i;

	i = -1;
	while (g_optab[op - 1].ocp[++i] != 0)
		if (ocp == g_optab[op - 1].ocp[i])
			return (ocp);
	return (-1);
}

int			ft_ocp(int op, char **param)
{
	int		ocp;
	int		p[3];
	int		i;

	if (!g_optab[op - 1].ocp[0])
		return (0);
	i = -1;
	while (++i < 3)
	{
		if (param[i])
			p[i] = ft_isparam(param[i]);
		else
			while (i < 3)
				p[i++] = 0;
	}
	ocp = 0;
	ocp += p[0];
	ocp = ocp << 2;
	ocp += p[1];
	ocp = ocp << 2;
	ocp += p[2];
	ocp = ocp << 2;
	return (ft_checkocp(op, ocp));
}
