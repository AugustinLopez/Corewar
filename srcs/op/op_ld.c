/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 14:41:33 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/30 11:08:04 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_ld_lld(t_vm *vm, t_process *proc)
{
	if (load_from_ocp(vm, proc, 2, (proc->op.op == 2) ? OP_IDX : OP_IND)
			 == FAILURE || !ft_strchr("\xd0\x90", (proc->op.ocp & 0xf0)))
		return (FAILURE);
	proc->r[proc->op.p[1] - 1] = ((proc->op.ocp & 0xf0) == 0xd0)
			? proc->op.ind[0] : proc->op.p[0];
	proc->carry = proc->r[proc->op.p[1] - 1] == 0 ? 1 : 0;
	return (0);
}
