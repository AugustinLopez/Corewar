/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 13:53:31 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/11 18:37:50 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_isskip(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isblank(str[i]))
		{
			if (str[i] == COM_CHAR)
				break ;
			else
				return (0);
		}
	return (1);
}

int			ft_isinfo(char *str)
{
	int		ret;
	int		i;
	int		j;

	ret = 0;
	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	j = 0;
	while (str[i + j] && !ft_isblank(str[i + j]) && str[i + j] != '"')
		j++;
	if (!ft_strncmp(NAME_CMD_STRING, str + i, ft_strlen(NAME_CMD_STRING)))
		ret = 1;
	else if (!ft_strncmp(COMMENT_CMD_STRING, str + i
		, ft_strlen(COMMENT_CMD_STRING)))
		ret = 2;
	return (ret);
}

int			ft_islabchar(char c)
{
	int		i;

	i = -1;
	while (LABEL_CHARS[++i])
		if (c == LABEL_CHARS[i])
			return (1);
	return (0);
}

int			ft_islab(char *str)
{
	int		lim;
	int		i;

	lim = ft_cpos(str, LABEL_CHAR);
	if (lim < 1)
		return (0);
	i = -1;
	while (++i < lim)
		if (!ft_islabchar(str[i]))
		{
			if (ft_isblank(str[i]) || str[i] == DIRECT_CHAR || str[i] == '-'
				|| str[i] == SEPARATOR_CHAR)
				return (0);
			else
				return (-1);
		}
	return (1);
}

int			ft_isop(char *str, int i, t_struct *s)
{
	int		j;
	int		k;

	j = -1;
	while (!ft_isblank(str[i + ++j]))
	{
		if (str[i + j] == DIRECT_CHAR || str[i + j] == '-')
			break ;
		if (!ft_isalpha(str[i + j]))
			return (0);
	}
	k = -1;
	while (++k < (s->bonus ? 22 : 16))
		if (!ft_strncmp(str + i, g_optab[k].name, j))
			break ;
	if (k < (s->bonus ? 22 : 16))
		return (k + 1);
	return (0);
}
