/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:37:25 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/26 17:52:20 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_st(t_vm *vm, t_process *proc)
{
	int	addr;
	int	ret;

	ret = SUCCESS;
	if (load_from_ocp(vm, proc, 2, OP_IDX) == FAILURE)
		ret = FAILURE;
	if (!ft_strchr("\x70\x50", (proc->op.ocp & 0xf0)))
	{
		proc->next_pc = (proc->next_pc + 1) % MEM_SIZE;
		ret = FAILURE;
	}
	if (ret == FAILURE)
		return (ret);
	if ((proc->op.ocp & 0xf0) == 0x50)
		proc->r[proc->op.p[1] - 1] = proc->r[proc->op.p[0] - 1];
	else
	{
		if ((addr = (proc->pc + proc->op.p[1] % IDX_MOD) % MEM_SIZE) < 0)
			addr = MEM_SIZE + addr % MEM_SIZE;
		write_in_ram(vm, proc, addr, proc->r[proc->op.p[0] - 1]);
	}
	return (0);
}
