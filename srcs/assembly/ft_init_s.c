/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 12:16:43 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/10 13:06:19 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_parse_args(t_struct *s, int ac, char **av)
{
	if (ac == 2)
		s->bonus = 0;
	else
	{
		if (av[1][0] != '-' || av[1][1] != 'b')
			ft_error(s, NULL, -1);
		s->bonus = 1;
	}
}

t_struct	*ft_init_s(int ac, char **av)
{
	t_struct	*s;

	if (!(s = (t_struct*)malloc(sizeof(t_struct))))
		ft_error(NULL, MALL_ERR, 0);
	s->rd = NULL;
	s->rderr = 0;
	ft_bzero(&s->header, sizeof(t_header));
	ft_bzero(s->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(s->header.comment, COMMENT_LENGTH + 1);
	s->oplist = NULL;
	s->lab = NULL;
	s->line = 1;
	ft_parse_args(s, ac, av);
	s->fname = av[ac - 1];
	s->prog = NULL;
	s->fcor = NULL;
	s->last_opcode = 0;
	return (s);
}
