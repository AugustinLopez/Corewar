/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:37:25 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/23 18:19:09 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_st(t_vm *vm, t_process *proc)
{
	int	addr;

	if ((proc->op.ocp & 0xf0) == 0x70 || (proc->op.ocp & 0xf0) == 0x50)
	{
		if (!(0 < proc->op.p[0] && proc->op.p[0] <= REG_NUMBER))
			return (0);
		if ((proc->op.ocp & 0xf0) == 0x50)
		{
			if (!(0 < proc->op.p[1] && proc->op.p[1] <= REG_NUMBER))
				return (0);
			proc->r[proc->op.p[1] - 1] = proc->r[proc->op.p[0] - 1];
		}
		else
		{
			addr = (proc->pc + 3) % MEM_SIZE;
			proc->op.p[1] = load_from_ram(vm, addr, 2);
			addr = proc->pc + proc->op.p[1] % IDX_MOD;
			if (addr < 0)
				addr = MEM_SIZE + addr % MEM_SIZE;
			write_in_ram(vm, proc, addr, proc->r[proc->op.p[0] - 1]);
		}
	}
	return (0);
}
