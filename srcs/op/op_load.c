/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:10:27 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/18 15:56:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

# define LOAD_DIRECT_2 1
# define LOAD_RESTRICT 2

static int insert_offset(t_process *proc, int nb_arg, int direct)
{
	int		i;
	uint8_t	temp;
	int		sum;

	i = 0;
	sum = 0;
	while (i < nb_arg)
	{
		temp = ((proc->op.ocp) >> ((3 - i) * 2)) & 0x3;
		if (temp == REG_CODE)
			proc->op.p[i] = 1;
		else if (temp == DIR_CODE)
			proc->op.p[i] = direct;
		else if (temp == IND_CODE)
			proc->op.p[i] = 2;
		else
			proc->op.p[i] = 0;
		sum += proc->op.p[i];
		++i;
	}
	return (sum);
}

void	op_load_one(t_vm *vm, t_process *proc, uint16_t cycle, uint8_t size)
{
	proc->cycle_to_wait = cycle - 1;
	proc->op.p[0] = load_from_ram(vm, proc->pc + 1, size);
	proc->next_pc = (proc->pc + 1 + size) % MEM_SIZE;
}

void	op_load_two(t_vm *vm, t_process *proc, uint16_t cycle, uint8_t flag)
{
	int	ret;
	int	direct;
	int	temp;
	int	temp2;

	direct = (flag & LOAD_DIRECT_2) ? 2 : 4;
	proc->cycle_to_wait = cycle - 1;
	proc->op.ocp = vm->ram[(proc->pc + 1) % MEM_SIZE].byte;
	ret = insert_offset(proc, 2, direct);
	temp = proc->op.p[0];
	temp2 = proc->op.p[1];
	proc->op.p[0] = load_from_ram(vm, proc->pc + 2, proc->op.p[0]);
	proc->op.p[1] = load_from_ram(vm, proc->pc + 2 + temp, proc->op.p[1]);
	if (temp == 2)
		proc->op.ind[0] = (flag & LOAD_RESTRICT)
			? load_from_ram(vm, proc->pc + proc->op.p[0] % IDX_MOD, 4)
			: load_from_ram(vm, proc->pc + proc->op.p[0], 4);
	if (temp2 == 2)
		proc->op.ind[1] = (flag & LOAD_RESTRICT)
			? load_from_ram(vm, proc->pc + proc->op.p[1] % IDX_MOD, 4)
			: load_from_ram(vm, proc->pc + proc->op.p[1], 4);
	proc->next_pc = (proc->pc + 2 + ret) % MEM_SIZE;
}

void	op_load_three(t_vm *vm, t_process *proc, uint16_t cycle, uint8_t flag)
{
	int	ret;
	int	direct;
	int	temp;
	int	temp2;
	int	temp3;

	direct = (flag & LOAD_DIRECT_2) ? 2 : 4;
	proc->cycle_to_wait = cycle - 1;
	proc->op.ocp = vm->ram[(proc->pc + 1) % MEM_SIZE].byte;
	ret = insert_offset(proc, 3, direct);
	temp = proc->op.p[0];
	temp2 = proc->op.p[1];
	temp3 = proc->op.p[2];
	proc->op.p[0] = load_from_ram(vm, proc->pc + 2, proc->op.p[0]);
	proc->op.p[1] = load_from_ram(vm, proc->pc + 2 + temp, proc->op.p[1]);
	proc->op.p[2] = load_from_ram(vm, proc->pc + 2 + temp2 + temp, proc->op.p[2]);
	if (temp == 2)
		proc->op.ind[0] = (flag & LOAD_RESTRICT)
			? load_from_ram(vm, proc->pc + proc->op.p[0] % IDX_MOD, 4)
			: load_from_ram(vm, proc->pc + proc->op.p[0], 4);
	if (temp2 == 2)
		proc->op.ind[1] = (flag & LOAD_RESTRICT)
			? load_from_ram(vm, proc->pc + proc->op.p[1] % IDX_MOD, 4)
			: load_from_ram(vm, proc->pc + proc->op.p[1], 4);
	if (temp3 == 2)
		proc->op.ind[2] = (flag & LOAD_RESTRICT)
			? load_from_ram(vm, proc->pc + proc->op.p[2] % IDX_MOD, 4)
			: load_from_ram(vm, proc->pc + proc->op.p[2], 4);
	proc->next_pc = (proc->pc + 2 + ret) % MEM_SIZE;
}

void	load_process(t_vm *vm, t_process *proc)
{
	vm->ram[proc->pc].process = FALSE;
	proc->op.op = vm->ram[proc->pc].byte;
	if (proc->op.op == 1)
		op_load_one(vm, proc, 10, 4);
	else if (proc->op.op == 2 || proc->op.op == 3)
		op_load_two(vm, proc, 5, LOAD_RESTRICT);
	else if (proc->op.op == 4 || proc->op.op == 5)
		op_load_three(vm, proc, 10, LOAD_RESTRICT);
	else if (6 <= proc->op.op && proc->op.op <= 8)
		op_load_three(vm, proc, 6, LOAD_RESTRICT);
	else if (proc->op.op == 9)
		op_load_one(vm, proc, 20, 2);
	else if (proc->op.op == 10 || proc->op.op == 11)
		op_load_three(vm, proc, 25, LOAD_DIRECT_2 | LOAD_RESTRICT);
	else if (proc->op.op == 12)
		op_load_one(vm, proc, 800, LOAD_DIRECT_2 | LOAD_RESTRICT);
	else if (proc->op.op == 13)
		op_load_two(vm, proc, 10, 0);
	else if (proc->op.op == 14)
		op_load_three(vm, proc, 50, LOAD_DIRECT_2);
	else if (proc->op.op == 15)
		op_load_one(vm, proc, 1000, LOAD_DIRECT_2);
	else if (proc->op.op == 16)
		op_load_one(vm, proc, 2, OFF_REG);
	else
		proc->next_pc = (proc->pc + 1) % MEM_SIZE;
}
