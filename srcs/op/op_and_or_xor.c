/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and_or_xor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:27:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 13:40:18 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_binary(t_vm *vm, t_process *proc)
{
	int	tp1;
	int	tp2;

	if (!(((proc->op.ocp & 0xFC) == 0x54) || ((proc->op.ocp & 0xFC) == 0x64)
				|| ((proc->op.ocp & 0xFC) == 0x74)
				|| ((proc->op.ocp & 0xFC) == 0x94)
				|| ((proc->op.ocp & 0xFC) == 0xA4)
				|| ((proc->op.ocp & 0xFC) == 0xB4)
				|| ((proc->op.ocp & 0xFC) == 0xD4)
				|| ((proc->op.ocp & 0xFC) == 0xE4)
				|| ((proc->op.ocp & 0xFC) == 0xF4)))
		return (FAILURE);
	if (0 < proc->op.p[2] && proc->op.p[2] <= REG_NUMBER)
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
		proc->r[proc->op.p[2] - 1] = tmp & tmp2;
	else if (proc->op.op == 7)
		proc->r[proc->op.p[2] - 1] = tmp | tmp2;
	else
		proc->r[proc->op.p[2] - 1] = tmp ^ tmp2;
	proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}
