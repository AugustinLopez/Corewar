/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 13:00:48 by algautie          #+#    #+#             */
/*   Updated: 2019/10/10 14:18:55 by algautie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../includes/op.h"

int			is_four_dir(int opc)
{
	if (g_optab[opc - 1].dir_sz == 4)
		return (1);
	return (0);
}

static void	fill_label(t_struct *s, int size)
{
	t_label *tmp;

	tmp = s->lab;
	while (tmp && tmp->address != -1)
		tmp = tmp->next;
	if (tmp)
		tmp->address = size;
}

static int	compute_size(t_struct *s)
{
	int			size;
	int			i;
	t_oplist	*tmp;

	size = 0;
	tmp = s->oplist;
	while (tmp)
	{
		if (tmp->op && (++size))
		{
			size += (tmp->ocp ? 1 : 0);
			i = -1;
			while (tmp->p[++i])
			{
				size += (ft_isreg(tmp->p[i]) ? 1 : 2);
				size += (ft_isdir(tmp->p[i]) && is_four_dir(tmp->op) ? 2 : 0);
			}
		}
		else if (!(tmp->op) && tmp->lab)
			fill_label(s, size);
		if (size > MEM_SIZE)
			ft_error(s, SIZE_ERR, -1);
		tmp = tmp->next;
	}
	return (size);
}

static void	fill_prog(t_struct *s)
{
	t_oplist	*tmp;
	int			j;

	tmp = s->oplist;
	s->index = 0;
	while (tmp)
	{
		j = -1;
		if (tmp->op)
		{
			if (tmp->op)
			{
				s->last_opcode = s->index;
				s->prog[s->index++] = tmp->op;
			}
			if (tmp->ocp)
				s->prog[s->index++] = tmp->ocp;
			while (tmp->p[++j])
				write_param(s, tmp->p[j], tmp->op);
		}
		tmp = tmp->next;
	}
}

void		write_cor(t_struct *s)
{
	int				fd;
	int				size;

	size = ft_strlen(s->fname);
	if (!(s->fcor = ft_strnjoin(s->fname, "cor", size - 1)))
		ft_error(s, MALL_ERR, -1);
	size = compute_size(s);
	s->header.prog_size = ft_reverse_bytes((unsigned int)size);
	s->header.magic = ft_reverse_bytes(COREWAR_EXEC_MAGIC);
	if (!(s->prog = (unsigned char*)malloc(sizeof(unsigned char) * size + 1)))
		ft_error(s, MALL_ERR, -1);
	ft_bzero(s->prog, size);
	s->prog[size] = '\0';
	fill_prog(s);
	if (!(fd = open(s->fcor, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 00644)))
		ft_error(s, OPEN_ERR, -1);
	ft_printf("Writing output program to %s\n", s->fcor);
	write(fd, &s->header, sizeof(t_header));
	write(fd, s->prog, size);
}
