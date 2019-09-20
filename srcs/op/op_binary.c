/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:27:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/20 13:16:58 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include <string.h>

int	op_binary(t_process *proc)
{
	int	tp1;
	int	tp2;

	tp1 = proc->op.ocp & 0xFC;
	if (!(ft_strchr("\x54\x64\x74\x94\xA4\xb4\xD4\xE4\xF4", tp1)))
		return (FAILURE);
	if (!(0 < proc->op.p[2] && proc->op.p[2] <= REG_NUMBER))
		return (FAILURE);
	if ((proc->op.ocp & 0xC0) == 0x40)
	{
		if (!(0 < proc->op.p[0] && proc->op.p[0] <= REG_NUMBER))
			return (FAILURE);
		tp1 = proc->r[proc->op.p[0] - 1];
	}
	else
		tp1 = ((proc->op.ocp & 0xC0) == 0x80) ? proc->op.p[0] : proc->op.ind[0];
	if ((proc->op.ocp & 0x30) == 0x10)
	{
		if (!(0 < proc->op.p[1] && proc->op.p[1] <= REG_NUMBER))
			return (FAILURE);
		tp2= proc->r[proc->op.p[0] - 1];
	}
	else
		tp2 = ((proc->op.ocp & 0x30) == 0x20) ? proc->op.p[1] : proc->op.ind[1];
	if (proc->op.op == 6)
		proc->r[proc->op.p[2] - 1] = tp1 & tp2;
	else if (proc->op.op == 7)
		proc->r[proc->op.p[2] - 1] = tp1 | tp2;
	else
		proc->r[proc->op.p[2] - 1] = tp1 ^ tp2;
	proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}
