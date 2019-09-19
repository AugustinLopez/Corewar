/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:37:25 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 14:31:00 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

void	write_in_ram(t_vm *vm, t_process *proc, int addr, int number)
{
	char a;
	char b;
	char c;
	char d;

	a = (number >> 24) & 0xff;
	b = (number >> 16) & 0xff;
	c = (number >> 8) & 0xff;
	d = (number >> 0) & 0xff;
	vm->ram[(addr + 0) % MEM_SIZE].byte = a;
	vm->ram[(addr + 0) % MEM_SIZE].write_total++;
	vm->ram[(addr + 0) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 0) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 1) % MEM_SIZE].byte = b;
	vm->ram[(addr + 1) % MEM_SIZE].write_total++;
	vm->ram[(addr + 1) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 1) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 2) % MEM_SIZE].byte = c;
	vm->ram[(addr + 2) % MEM_SIZE].write_total++;
	vm->ram[(addr + 2) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 2) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 3) % MEM_SIZE].byte = d;
	vm->ram[(addr + 3) % MEM_SIZE].write_total++;
	vm->ram[(addr + 3) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 3) % MEM_SIZE].player_last = proc->player_id;
}

int		op_st(t_vm *vm, t_process *proc)
{
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
			write_in_ram(vm, proc, proc->pc + proc->op.p[1] % IDX_MOD, proc->r[proc->op.p[0] - 1]);
	}
	return (0);
}
