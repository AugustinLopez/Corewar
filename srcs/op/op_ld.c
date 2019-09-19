/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:41:33 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 16:07:53 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_ld_lld(t_vm *vm, t_process *proc)
{
	int tmp;

	if (!(((proc->op.ocp & 0xf0) == 0xD0) || ((proc->op.ocp & 0xf0) == 0x90)))
		return (FAILURE);
	tmp = ((proc->op.ocp & 0xf0) == 0xD0) ? (proc->op.ind[0]) : (proc->op.p[0]);
	if (0 < proc->op.p[1] && proc->op.p[1] <= REG_NUMBER)
	{
		if (proc->op.op == 13 && (proc->op.ocp & 0xf0) == 0xd0)
			proc->r[proc->op.p[1] - 1] = tmp >> 16;
		else if ((proc->op.ocp & 0xf0) == 0xD0)
			proc->r[proc->op.p[1] - 1] = load_from_ram(vm, proc->pc + tmp, 4);
		else if ((proc->op.ocp & 0xf0) == 0x90)
			proc->r[proc->op.p[1] - 1] = tmp;
	}
	proc->carry = tmp == 0 ? 1 : 0;
	return (0);
}
