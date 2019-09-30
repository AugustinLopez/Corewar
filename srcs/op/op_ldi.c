/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 10:19:51 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/30 11:08:43 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_ldi_lldi(t_vm *vm, t_process *proc)
{
	int	addr;

	if (load_from_ocp(vm, proc, 3, OP_DIR | OP_IDX) == FAILURE
			|| !ft_strchr("\x54\x64\x94\xa4\xd4\xe4", (proc->op.ocp & 0xfc)))
		return (FAILURE);
	if ((proc->op.ocp & 0xC0) == 0x40)
		proc->op.p[0] = proc->r[proc->op.p[0] - 1];
	else if ((proc->op.ocp & 0xc0) == 0xc0)
		proc->op.p[0] = proc->op.ind[0];
	if ((proc->op.ocp & 0x30) == 0x10)
		proc->op.p[1] = proc->r[proc->op.p[1] - 1];
	addr = proc->op.op == 10
			? proc->pc + (proc->op.p[0] + proc->op.p[1]) % IDX_MOD
			: proc->pc + (proc->op.p[0] + proc->op.p[1]);
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	proc->r[proc->op.p[2] - 1] = load_from_ram(vm, addr, 4);
	if (proc->op.op == 14)
		proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}
