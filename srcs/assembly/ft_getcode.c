/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:57 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/11 17:26:31 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_getlab(t_struct *s, int i)
{
	char	*lab;
	int		lim;

	lim = ft_cpos(s->rd->data + i, LABEL_CHAR);
	lab = ft_strsub(s->rd->data, i, lim);
	if (!s->oplist)
		s->oplist = ft_init_oplab(s, lab);
	else
		ft_pushback_op(s, ft_init_oplab(s, lab));
	if (!s->lab)
		s->lab = ft_init_lab(s, lab);
	else
		ft_pushback_lab(s, ft_init_lab(s, lab));
	i += lim + 1;
	return (i);
}

static t_oplist	*ft_init_op(t_struct *s, int op, char **param)
{
	t_oplist	*ope;
	int			ocp;

	if ((ocp = ft_ocp(op, param)) < 0)
	{
		ft_free_strtab(param);
		ft_error(s, PAR_OP, 0);
	}
	if (!(ope = (t_oplist*)malloc(sizeof(t_oplist))))
	{
		ft_free_strtab(param);
		ft_error(s, MALL_ERR, 0);
	}
	ope->op = op;
	ope->ocp = ocp;
	ope->p = param;
	ope->lab = NULL;
	ope->next = NULL;
	return (ope);
}

static void		ft_getop(t_struct *s, int i)
{
	int		op;
	char	**param;

	if ((op = ft_isop(s->rd->data, i, s)))
		i += g_optab[op - 1].nsize;
	else
		ft_error(s, INV_OP, 0);
	param = ft_getparam(s, i);
	ft_checkparam(s, param, op);
	if (!s->oplist)
		s->oplist = ft_init_op(s, op, param);
	else
		ft_pushback_op(s, ft_init_op(s, op, param));
}

void			ft_getcode(t_struct *s)
{
	int		i;
	int		lab;

	while (s->rd)
	{
		while (s->rd && ft_isskip(s->rd->data))
			ft_next_rd(s);
		if (s->rd)
		{
			i = 0;
			while (s->rd->data[i] && ft_isblank(s->rd->data[i]))
				i++;
			if ((lab = ft_islab(s->rd->data + i)) == 1)
				i = ft_getlab(s, i);
			else if (lab == -1)
				ft_error(s, INV_LABCHAR, 0);
			while (s->rd->data[i] && ft_isblank(s->rd->data[i]))
				i++;
			if (s->rd->data[i] && s->rd->data[i] != COM_CHAR)
				ft_getop(s, i);
			ft_next_rd(s);
		}
	}
	if (!s->oplist)
		ft_error(s, EMPTY_CODE, -1);
}
