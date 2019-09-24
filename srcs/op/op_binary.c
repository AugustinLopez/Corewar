/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_binary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 12:27:17 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/23 17:00:01 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include <string.h>

int	op_binary(t_vm *vm, t_process *proc)
{
	if (load_from_ocp(vm, proc, 3, OP_IDX) == FAILURE
			|| !ft_strchr("\x54\x64\x74\x94\xA4\xb4\xd4\xe4\xf4", (proc->op.ocp & 0xfc)))
	if ((proc->op.ocp & 0xC0) == 0x40)
		proc->op.p[0] = proc->r[proc->op.p[0] - 1];
	else if ((proc->op.ocp & 0xC0) == 0xC0)
		proc->op.p[0] = proc->op.ind[0];
	if ((proc->op.ocp & 0x30) == 0x10)
		proc->op.p[1] = proc->r[proc->op.p[1] - 1];
	else if ((proc->op.ocp & 0x30) == 0x30)
		proc->op.p[1] = proc->op.ind[1];
	if (proc->op.op == 6)
		proc->r[proc->op.p[2] - 1] = proc->op.p[0] & proc->op.p[1];
	else if (proc->op.op == 7)
		proc->r[proc->op.p[2] - 1] = proc->op.p[0] | proc->op.p[1];
	else
		proc->r[proc->op.p[2] - 1] = proc->op.p[0] ^ proc->op.p[1];
	proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}
