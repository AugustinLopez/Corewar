/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:19:51 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 15:50:30 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_ldi_lldi(t_vm *vm, t_process *proc)
{
	int	tmp;
	int	tmp2;
	int	addr;

	if (!(((proc->op.ocp & 0xFC) == 0x54) || ((proc->op.ocp & 0xFC) == 0x64)
				|| ((proc->op.ocp & 0xFC) == 0x94)
				|| ((proc->op.ocp & 0xFC) == 0xA4)
				|| ((proc->op.ocp & 0xFC) == 0xD4)
				|| ((proc->op.ocp & 0xFC) == 0xE4)))
		return (FAILURE);
	if (!(0 < proc->op.p[2] && proc->op.p[2] <= REG_NUMBER))
		return (FAILURE);
	if ((proc->op.ocp & 0xC0) == 0x40)
	{
		if (!(0 < proc->op.p[0] && proc->op.p[0] <= REG_NUMBER))
			return (FAILURE);
		tmp = proc->r[proc->op.p[0] - 1];
	}
	else
		tmp = (proc->op.op != 10 || (proc->op.ocp & 0xC0) == 0x80) ? proc->op.p[0] : proc->op.ind[0];
	if ((proc->op.ocp & 0x30) == 0x10)
	{
		if (!(0 < proc->op.p[1] && proc->op.p[1] <= REG_NUMBER))
			return (FAILURE);
		tmp2 = proc->r[proc->op.p[1] - 1];
	}
	else
		tmp2 = proc->op.p[1];
	addr = proc->op.op == 10 ? (tmp + tmp2) % IDX_MOD : (tmp + tmp2);
	proc->r[proc->op.p[2] - 1] = load_from_ram(vm, proc->pc + addr, 4);
	if (proc->op.op == 14)
		proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}
