/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:09:01 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/18 16:37:12 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"


int		op_fork_lfork(t_vm *vm, t_process *proc)
{
	if (proc->op.op == 12)
	{
		if (create_process(vm, proc->pc + proc->op.p[0] % IDX_MOD, proc->player_id) == FAILURE)
			return (FAILURE);
		vm->process->carry = proc->carry;
		ft_memcpy(vm->process->r, proc->r, sizeof(proc->r));
	}
	else
	{
		if (create_process(vm, proc->pc + proc->op.p[0], proc->player_id) == FAILURE)
			return (FAILURE);
		vm->process->carry = proc->carry;
		ft_memcpy(vm->process->r, proc->r, sizeof(proc->r));

	}
	return (SUCCESS);
}
