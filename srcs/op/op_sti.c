/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:03:27 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 12:09:31 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_sti(t_vm *vm, t_process *proc)
{
	int	tmp;
	int	tmp2;
	int	addr;

	if (!(((proc->op.ocp & 0xFC) == 0x54) || ((proc->op.ocp & 0xFC) == 0x64)
				|| ((proc->op.ocp & 0xFC) == 0x74)
				|| ((proc->op.ocp & 0xFC) == 0x58)
				|| ((proc->op.ocp & 0xFC) == 0x68)
				|| ((proc->op.ocp & 0xFC) == 0x78)))
		return (FAILURE);
	if (!(0 < proc->op.p[0] && proc->op.p[0] <= REG_NUMBER))
			return (FAILURE);
	if ((proc->op.ocp & 0x30) == 0x10)
	{
		if (!(0 < proc->op.p[1] && proc->op.p[1] <= REG_NUMBER))
			return (FAILURE);
		tmp = proc->r[proc->op.p[1] - 1];
	}
	else
		tmp = ((proc->op.ocp & 0x30) == 0x20) ? proc->op.p[1] : proc->op.ind[1];
	if ((proc->op.ocp & 0xC) == 0x4)
	{
		if (!(0 < proc->op.p[2] && proc->op.p[2] <= REG_NUMBER))
			return (FAILURE);
		tmp2 = proc->r[proc->op.p[2] - 1];
	}
	else
		tmp2 = proc->op.p[2];
	addr = (tmp + tmp2) % IDX_MOD;
	write_in_ram(vm, proc, addr, proc->r[proc->op.p[0] - 1]);
	return (SUCCESS);
}
