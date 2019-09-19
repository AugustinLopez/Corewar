/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:18:35 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 12:26:58 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_arithmetic(t_vm *vm, t_process *proc)
{
	if (!((proc->op.ocp & 0xFC) == 0x54))
		return (FAILURE);
	if (0 < proc->op.p[0] && proc->op.p[0] <= REG_NUMBER)
		return (FAILURE);
	if (0 < proc->op.p[1] && proc->op.p[1] <= REG_NUMBER)
		return (FAILURE);
	if (0 < proc->op.p[2] && proc->op.p[2] <= REG_NUMBER)
		return (FAILURE);
	if (proc->op.op == 4)
		proc->r[proc->op[2] - 1] = proc->r[proc->op[1] - 1]
			+ proc->r[proc->op[0] - 1];
	else
		proc->r[proc->op[2] - 1] = proc->r[proc->op[1] - 1]
			- proc->r[proc->op[0] - 1];
	proc->carry = proc->r[proc->op[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}
