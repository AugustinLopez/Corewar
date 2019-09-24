/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:03:27 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/20 15:49:20 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_sti(t_vm *vm, t_process *proc)
{
	int	addr;

	if (load_from_ocp(vm, proc, 3, OP_DIR | OP_IDX) == FAILURE
			|| !ft_strchr("\x54\x64\x74\x58\x68\x78", (proc->op.ocp & 0xfc)))
		return (FAILURE);
	if ((proc->op.ocp & 0x30) == 0x10)
		proc->op.p[1] = proc->r[(proc->op.p[1] - 1)];
	else if ((proc->op.ocp & 0x30) == 0x30)
		proc->op.p[1] = proc->op.ind[1];
	if ((proc->op.ocp & 0xC) == 0x4)
		proc->op.p[2] = proc->r[(proc->op.p[2] - 1)];
	addr = proc->pc + (proc->op.p[1] + proc->op.p[2]) % IDX_MOD;
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	write_in_ram(vm, proc, addr, proc->r[proc->op.p[0] - 1]);
	return (SUCCESS);
}
