/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:10:27 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/23 14:49:42 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

static int	insert_offset(t_process *proc, int nb_arg, int direct)
{
	int		i;
	uint8_t	tmp;
	int		sum;

	i = 0;
	sum = 0;
	while (i < nb_arg)
	{
		tmp = ((proc->op.ocp) >> ((3 - i) * 2)) & 0x3;
		if (tmp == REG_CODE)
			proc->op.p[i] = 1;
		else if (tmp == DIR_CODE)
			proc->op.p[i] = direct;
		else if (tmp == IND_CODE)
			proc->op.p[i] = 2;
		else
			proc->op.p[i] = 0;
		sum += proc->op.p[i];
		++i;
	}
	return (sum);
}

void		op_load_one(t_vm *vm, t_process *proc, uint16_t cycle, uint8_t size)
{
	int	ret;
	int	addr;

	proc->cycle_to_wait = cycle - 1;
	if (proc->op.op == 16)
	{
		proc->op.ocp = vm->ram[(proc->pc + 1) % MEM_SIZE].byte;
		ret = insert_offset(proc, 1, 4);
		addr = (proc->pc + 2) % MEM_SIZE;
		proc->op.p[0] = load_from_ram(vm, addr, size);
		proc->next_pc = (addr + ret) % MEM_SIZE;
	}
	else
	{
		addr = (proc->pc + 1) % MEM_SIZE;
		proc->op.p[0] = load_from_ram(vm, addr, size);
		proc->next_pc = (addr + size) % MEM_SIZE;
	}
}

void		op_load_two(t_vm *vm, t_process *proc, uint16_t cycle, uint8_t flag)
{
	int	ret;
	int	i;
	int	tmp[2];
	int	addr;

	i = (flag & OP_DIRECT_2) ? 2 : 4;
	proc->cycle_to_wait = cycle - 1;
	proc->op.ocp = vm->ram[(proc->pc + 1) % MEM_SIZE].byte;
	ret = insert_offset(proc, 2, i);
	ft_memcpy(tmp, proc->op.p, sizeof(tmp));
	addr = (proc->pc + 2) % MEM_SIZE;
	proc->op.p[0] = load_from_ram(vm, addr, proc->op.p[0]);
	if ((addr = (addr + tmp[0]) % MEM_SIZE) < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	proc->op.p[1] = load_from_ram(vm, addr, proc->op.p[1]);
	i = 0;
	while (i < 2)
	{
		if (tmp[i] == 2)
		{
			addr = (flag & OP_RESTRICT)
				? (proc->pc + proc->op.p[i] % IDX_MOD) % MEM_SIZE
				: (proc->pc + proc->op.p[i]) % MEM_SIZE;
			if (addr < 0)
				addr = MEM_SIZE + (addr % MEM_SIZE);
			proc->op.ind[i] = load_from_ram(vm, addr, 4);
			}
		++i;
	}
	if ((addr = (proc->pc + 2 + ret) % MEM_SIZE) < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	proc->next_pc = addr;
}

void		op_load_three(t_vm *vm, t_process *pr, uint16_t cycle, uint8_t flag)
{
	int	ret;
	int	i;
	int	tmp[3];
	int	addr;

	i = (flag & OP_DIRECT_2) ? 2 : 4;
	pr->cycle_to_wait = cycle - 1;
	pr->op.ocp = vm->ram[(pr->pc + 1) % MEM_SIZE].byte;
	ret = insert_offset(pr, 3, i);
	ft_memcpy(tmp, pr->op.p, sizeof(tmp));
	addr = (pr->pc + 2) % MEM_SIZE;
	pr->op.p[0] = load_from_ram(vm, addr, pr->op.p[0]);
	if ((addr = (addr + tmp[0]) % MEM_SIZE) < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	pr->op.p[1] = load_from_ram(vm, pr->pc + 2 + tmp[0], pr->op.p[1]);
	if ((addr = (addr + tmp[1]) % MEM_SIZE) < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	pr->op.p[2] = load_from_ram(vm, pr->pc + 2 + tmp[1] + tmp[0], pr->op.p[2]);
	i = 0;
	while (i < 3)
	{
		if (tmp[i] == 2)
		{
			addr = (flag & OP_RESTRICT)
				? (pr->pc + pr->op.p[i] % IDX_MOD) % MEM_SIZE
				: (pr->pc + pr->op.p[i]) % MEM_SIZE;
			if (addr < 0)
				addr = MEM_SIZE + (addr % MEM_SIZE);
			pr->op.ind[i] = load_from_ram(vm, addr, 4);
			}
		++i;
	}
	if ((addr = (pr->pc + 2 + ret) % MEM_SIZE) < 0)
		addr = MEM_SIZE + (addr % MEM_SIZE);
	pr->next_pc = addr;
}

void		load_process(t_vm *vm, t_process *proc)
{
	if (proc->op.op == 1)
		op_load_one(vm, proc, 10, 4);
	else if (proc->op.op == 2 || proc->op.op == 3)
		op_load_two(vm, proc, 5, OP_RESTRICT);
	else if (proc->op.op == 4 || proc->op.op == 5)
		op_load_three(vm, proc, 10, OP_RESTRICT);
	else if (6 <= proc->op.op && proc->op.op <= 8)
		op_load_three(vm, proc, 6, OP_RESTRICT);
	else if (proc->op.op == 9)
		op_load_one(vm, proc, 20, 2);
	else if (proc->op.op == 10 || proc->op.op == 11)
		op_load_three(vm, proc, 25, OP_DIRECT_2 | OP_RESTRICT);
	else if (proc->op.op == 12)
		op_load_one(vm, proc, 800, 2);
	else if (proc->op.op == 13) //here
		op_load_two(vm, proc, 10, 0);
	else if (proc->op.op == 14)
		op_load_three(vm, proc, 50, OP_DIRECT_2);
	else if (proc->op.op == 15)
		op_load_one(vm, proc, 1000, 2);
	else if (proc->op.op == 16)
		op_load_one(vm, proc, 2, OFF_REG + 1);
	else
		proc->next_pc = (proc->pc + 1) % MEM_SIZE;
}
