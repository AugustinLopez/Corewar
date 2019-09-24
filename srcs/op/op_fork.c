/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:09:01 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/23 17:58:25 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include <errno.h>

int		op_fork_lfork(t_vm *vm, t_process *proc)
{
	int	addr;

	proc->next_pc = (proc->pc + 3) % MEM_SIZE;
	proc->op.p[0] = load_from_ram(vm, (proc->pc + 1) % MEM_SIZE, 2);
	addr = proc->op.op == 15 ? (proc->pc + proc->op.p[0]) % MEM_SIZE
		: (proc->pc + proc->op.p[0] % IDX_MOD) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	if (create_process(vm, addr, proc->player_id) == FAILURE)
	{
		vm->err = errno;
		return (FAILURE);
	}
	vm->process->carry = proc->carry;
	if (proc->alive == TRUE)
	{
		vm->process->alive = TRUE;
		++(vm->live_since_check);
	}
	ft_memcpy(vm->process->r, proc->r, sizeof(proc->r));
	analyze_process(vm, vm->process);
	return (SUCCESS);
}
