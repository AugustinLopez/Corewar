/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 12:28:22 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/27 12:54:46 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_arithmetic2(t_vm *vm, t_process *proc)
{
	if (load_from_ocp(vm, proc, 3, OP_IDX) == FAILURE
			|| !((proc->op.ocp & 0xFC) == 0x54)
			|| (proc->op.op != 17 && proc->r[proc->op.p[1] - 1] == 0))
		return (FAILURE);
	if (proc->op.op == 17)
		proc->r[proc->op.p[2] - 1] = proc->r[proc->op.p[0] - 1]
			* proc->r[proc->op.p[1] - 1];
	else if (proc->op.op == 18)
		proc->r[proc->op.p[2] - 1] = proc->r[proc->op.p[0] - 1]
			/ proc->r[proc->op.p[1] - 1];
	else
		proc->r[proc->op.p[2] - 1] = proc->r[proc->op.p[0] - 1]
			% proc->r[proc->op.p[1] - 1];
	proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}

int	op_binary2(t_vm *vm, t_process *proc)
{
	int	ret;

	ret = SUCCESS;
	if (load_from_ocp(vm, proc, 3, OP_IDX) == FAILURE
		|| !ft_strchr("\x54\x64\x74\x94\xA4\xb4\xd4\xe4\xf4"
		, (proc->op.ocp & 0xfc)))
		return (FAILURE);
	if ((proc->op.ocp & 0xC0) == 0x40)
		proc->op.p[0] = proc->r[proc->op.p[0] - 1];
	else if ((proc->op.ocp & 0xC0) == 0xC0)
		proc->op.p[0] = proc->op.ind[0];
	if ((proc->op.ocp & 0x30) == 0x10)
		proc->op.p[1] = proc->r[proc->op.p[1] - 1];
	else if ((proc->op.ocp & 0x30) == 0x30)
		proc->op.p[1] = proc->op.ind[1];
	if (proc->op.p[1] >= 31)
		proc->r[proc->op.p[2] - 1] = 0;
	else if (proc->op.p[1] < 0 && proc->op.op == 20);
		proc->r[proc->op.p[2] - 1] = proc->op.p[0] >> proc->op.p[1];
	if (proc->op.p[1] < 0)
		proc->r[proc->op.p[2] - 1] = proc->op.p[0] << proc->op.p[1];
	proc->carry = proc->r[proc->op.p[2] - 1] == 0 ? 1 : 0;
	return (SUCCESS);
}

int	op_carry(t_vm *vm, t_process *proc)
{
	proc->next_pc = (proc->pc + 3) % MEM_SIZE;
	proc->op.p[0] = load_from_ram(vm, (proc->pc + 1) % MEM_SIZE, 2);
	proc->carry = proc->op.p[0] == 0 ? 1 : 0;
	return (SUCCESS);
}
