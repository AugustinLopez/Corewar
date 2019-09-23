/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:41:09 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/23 10:56:48 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int	op_zjmp(t_process *proc)
{
	int	addr;

	addr = (proc->carry == 1)
		? (proc->pc + proc->op.p[0] % IDX_MOD) % MEM_SIZE
		: (proc->pc + 3) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	proc->next_pc = addr;
	return (SUCCESS);
}
