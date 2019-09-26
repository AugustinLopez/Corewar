/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ram.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/26 11:01:32 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <unistd.h>

void				write_in_ram(t_vm *vm, t_process *proc, int addr,
						int number)
{
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	vm->ram[(addr + 0) % MEM_SIZE].byte = (number >> 24) & 0xff;
	vm->ram[(addr + 0) % MEM_SIZE].write_total++;
	vm->ram[(addr + 0) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 0) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 1) % MEM_SIZE].byte = (number >> 16) & 0xff;
	vm->ram[(addr + 1) % MEM_SIZE].write_total++;
	vm->ram[(addr + 1) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 1) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 2) % MEM_SIZE].byte = (number >> 8) & 0xff;
	vm->ram[(addr + 2) % MEM_SIZE].write_total++;
	vm->ram[(addr + 2) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 2) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 3) % MEM_SIZE].byte = number & 0xff;
	vm->ram[(addr + 3) % MEM_SIZE].write_total++;
	vm->ram[(addr + 3) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 3) % MEM_SIZE].player_last = proc->player_id;
}

int					load_from_ram(t_vm *vm, size_t pc, int nbr)
{
	int		ret;
	short	ret2;

	pc %= MEM_SIZE;
	if (nbr == 1)
		return (vm->ram[pc].byte);
	if (nbr == 2)
	{
		ret2 = vm->ram[pc].byte << 8;
		pc = (pc + 1) % MEM_SIZE;
		ret2 |= vm->ram[pc].byte;
		return (ret2);
	}
	ret = vm->ram[pc].byte << 24;
	pc = (pc + 1) % MEM_SIZE;
	ret |= vm->ram[pc].byte << 16;
	pc = (pc + 1) % MEM_SIZE;
	ret |= vm->ram[pc].byte << 8;
	pc = (pc + 1) % MEM_SIZE;
	ret |= vm->ram[pc].byte;
	return (ret);
}

static inline int	load_ind(t_vm *vm, t_process *proc, int addr, uint8_t flag)
{
	int	ret;

	if (flag & OP_IDX)
		addr = (proc->pc + addr % IDX_MOD) % MEM_SIZE;
	else
		addr = (proc->pc + addr) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	ret = load_from_ram(vm, addr, (flag & OP_IND) ? 2 : 4);
	return (ret);
}

static inline int	load_offset(t_vm *vm, t_process *proc, int i, uint8_t flag)
{
	int	ocp;
	int	tmp;

	ocp = ((proc->op.ocp) >> ((4 - i) * 2)) & 0x3;
	if (ocp == REG_CODE)
		proc->op.p[i - 1] = 1;
	else if (ocp == DIR_CODE)
		proc->op.p[i - 1] = (flag & OP_DIR) ? 2 : 4;
	else if (ocp == IND_CODE)
		proc->op.p[i - 1] = 2;
	else
		proc->op.p[i - 1] = 0;
	tmp = proc->op.p[i - 1];
	proc->op.p[i - 1] = load_from_ram(vm, (proc->next_pc + 1) % MEM_SIZE
			, proc->op.p[i - 1]);
	proc->next_pc = (proc->next_pc + tmp) % MEM_SIZE;
	return (ocp);
}

t_bool				load_from_ocp(t_vm *vm, t_process *proc, int nbr_arg,
		uint8_t flag)
{
	int		i;
	int		ocp;
	t_bool	ret;

	ret = TRUE;
	i = 0;
	proc->op.ocp = load_from_ram(vm, (proc->pc + 1) % MEM_SIZE, 1);
	proc->next_pc = proc->pc + 1;
	while (i++ < nbr_arg)
	{
		ocp = load_offset(vm, proc, i, flag);
		if (ocp == 0 || (ocp == REG_CODE
				&& !(0 < proc->op.p[i - 1] && proc->op.p[i - 1] <= REG_NUMBER)))
			ret = FALSE;
		if (ocp == IND_CODE)
			proc->op.ind[i - 1] = load_ind(vm, proc, proc->op.p[i - 1], flag);
	}
	proc->next_pc = (proc->next_pc + 1) % MEM_SIZE;
	return (ret);
}
