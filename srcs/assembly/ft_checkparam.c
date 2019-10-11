/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkparam.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 16:23:07 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/09 12:13:08 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_format_dir(char *str)
{
	char		*ret;
	char		*tmp;
	long		nb;

	if (str[1] == '0' && str[2] == 'X')
	{
		tmp = ft_ismxlong(str + 3) ? ft_lconvert_base(str + 3
			, "0123456789ABCDEF", "0123456789")
				: ft_strdup("9223372036854775807");
		free(str);
		str = ft_joincstr(DIRECT_CHAR, tmp);
		free(tmp);
	}
	if (str[1] == ':')
		return (str);
	else if (!ft_islong(str + 1))
		nb = str[1] == '-' ? 0 : 9223372036854775807;
	else
		nb = (str[1] == '-' ? LONG_MAX : -1) + ft_atol(str + 1) + 1;
	tmp = ft_ltoa((unsigned int)nb);
	ret = ft_joincstr(DIRECT_CHAR, tmp);
	free(tmp);
	free(str);
	return (ret);
}

static char	*ft_format_ind(char *str)
{
	char	*ret;
	char	*tmp;
	long	nb;

	if (str[0] == '0' && str[1] == 'X')
	{
		tmp = ft_ismxlong(str + 2) ? ft_lconvert_base(str + 2
			, "0123456789ABCDEF", "0123456789")
				: ft_strdup("9223372036854775807");
		free(str);
		str = tmp;
	}
	if (str[0] == ':')
		return (str);
	else if (!ft_islong(str))
		nb = str[0] == '-' ? 0 : 9223372036854775807;
	else
		nb = (str[0] == '-' ? LONG_MAX : -1) + ft_atol(str) + 1;
	ret = ft_itoa((unsigned short)nb);
	free(str);
	return (ret);
}

static void	ft_check_format(t_struct *s, char **param)
{
	int		i;
	int		type;

	i = -1;
	while (param[++i])
		if (!(type = ft_isparam(param[i])))
		{
			ft_free_strtab(param);
			ft_error(s, INV_PAR, i + 1);
		}
		else if (type == 2)
			param[i] = ft_format_dir(param[i]);
		else if (type == 3)
			param[i] = ft_format_ind(param[i]);
}

void		ft_checkparam(t_struct *s, char **param, int op)
{
	int		i;

	i = -1;
	while (param[++i] && i <= 4)
		param[i] = ft_strtrimfree(param[i]);
	if (i != g_optab[op - 1].nbparam)
	{
		ft_free_strtab(param);
		ft_error(s, INV_NB_PAR, 0);
	}
	ft_check_format(s, param);
	if (!g_optab[op - 1].ocp[0] && !ft_isdir(param[0]))
	{
		ft_free_strtab(param);
		ft_error(s, PAR_OP, 0);
	}
}
