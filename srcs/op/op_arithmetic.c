/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_arithmetic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:18:35 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/30 11:06:39 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_arithmetic(t_vm *vm, t_process *proc)
{
	if (load_from_ocp(vm, proc, 3, OP_IDX) == FAILURE
			|| !((proc->op.ocp & 0xFC) == 0x54))
		return (FAILURE);
	if (proc->op.op == 4)
		proc->r[proc->op.p[2] - 1] = proc->r[proc->op.p[0] - 1]
			+ proc->r[proc->op.p[1] - 1];
	else
		proc->r[proc->op.p[2] - 1] = proc->r[proc->op.p[0] - 1]
			- proc->r[proc->op.p[1] - 1];
	proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}
