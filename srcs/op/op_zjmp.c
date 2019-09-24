/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:41:09 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/23 16:53:44 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int	op_zjmp(t_vm *vm, t_process *proc)
{
	int	addr;

	proc->op.p[0] = load_from_ram(vm, (proc->pc + 1) % MEM_SIZE, 2);
	addr = (proc->carry == 0) ? (proc->pc + 3) % MEM_SIZE
		: (proc->pc + proc->op.p[0] % IDX_MOD) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	proc->next_pc = addr;
	return (SUCCESS);
}
