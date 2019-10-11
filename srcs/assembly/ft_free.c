/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:53:37 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/09 11:53:07 by algautie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_free_rd(t_rd *rd)
{
	if (rd)
	{
		if (rd->next)
			ft_free_rd(rd->next);
		free(rd->data);
		free(rd);
	}
}

static void	ft_free_oplist(t_oplist *oplist)
{
	t_oplist	*tmp;

	while (oplist)
	{
		tmp = oplist;
		oplist = oplist->next;
		if (!tmp->op)
			free(tmp->lab);
		else
			ft_free_strtab(tmp->p);
		free(tmp);
	}
}

static void	ft_free_lab(t_label *lab)
{
	t_label	*tmp;

	while (lab)
	{
		tmp = lab;
		lab = lab->next;
		free(tmp);
	}
}

void		ft_free_s(t_struct *s)
{
	if (s->rd)
		ft_free_rd(s->rd);
	if (s->oplist)
		ft_free_oplist(s->oplist);
	if (s->lab)
		ft_free_lab(s->lab);
	if (s->fcor)
		free(s->fcor);
	if (s->prog)
		free(s->prog);
	free(s);
}
