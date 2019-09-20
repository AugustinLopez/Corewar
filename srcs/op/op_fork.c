/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:09:01 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/20 15:12:10 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include <errno.h>

int		op_fork_lfork(t_vm *vm, t_process *proc)
{
	int	addr;

	addr = proc->op.op == 12
		? proc->pc + proc->op.p[0] % IDX_MOD
		: proc->pc + proc->op.p[0];
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	if (create_process(vm, addr, proc->player_id) == FAILURE)
	{
		vm->err = errno;
		return (FAILURE);
	}
	vm->process->carry = proc->carry;
	ft_memcpy(vm->process->r, proc->r, sizeof(proc->r));
	return (SUCCESS);
}
