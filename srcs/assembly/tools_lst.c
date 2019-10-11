/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:16:36 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/08 17:15:32 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_next_rd(t_struct *s)
{
	t_rd	*tmp;

	tmp = s->rd;
	s->rd = s->rd->next;
	if (tmp->data)
		free(tmp->data);
	free(tmp);
	s->line++;
}

t_label		*ft_init_lab(t_struct *s, char *lab)
{
	t_label	*label;

	if (!(label = (t_label*)malloc(sizeof(t_label))))
	{
		free(lab);
		ft_error(s, MALL_ERR, 0);
	}
	label->name = lab;
	label->address = -1;
	label->next = NULL;
	return (label);
}

t_oplist	*ft_init_oplab(t_struct *s, char *lab)
{
	t_oplist	*oplist;

	if (!(oplist = (t_oplist*)malloc(sizeof(t_oplist))))
	{
		free(lab);
		ft_error(s, MALL_ERR, 0);
	}
	oplist->op = 0;
	oplist->ocp = 0;
	oplist->p = NULL;
	oplist->lab = lab;
	oplist->next = NULL;
	return (oplist);
}

void		ft_pushback_op(t_struct *s, t_oplist *oplist)
{
	t_oplist	*beg;

	beg = s->oplist;
	while (s->oplist->next)
		s->oplist = s->oplist->next;
	s->oplist->next = oplist;
	s->oplist = beg;
}

void		ft_pushback_lab(t_struct *s, t_label *lab)
{
	t_label *beg;

	beg = s->lab;
	while (s->lab->next)
		s->lab = s->lab->next;
	s->lab->next = lab;
	s->lab = beg;
}
