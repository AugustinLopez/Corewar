/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_load.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 13:10:27 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/20 11:09:52 by bcarlier         ###   ########.fr       */
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
	proc->cycle_to_wait = cycle - 1;
	if (proc->op.op == 16) //verifier
		proc->op.p[0] = load_from_ram(vm, proc->pc + 2, size);
	else
		proc->op.p[0] = load_from_ram(vm, proc->pc + 1, size);
	proc->next_pc = (proc->pc + 1 + size) % MEM_SIZE;
}

void		op_load_two(t_vm *vm, t_process *proc, uint16_t cycle, uint8_t flag)
{
	int	ret;
	int	direct;
	int	tmp[2];

	direct = (flag & OP_DIRECT_2) ? 2 : 4;
	proc->cycle_to_wait = cycle - 1;
	proc->op.ocp = vm->ram[(proc->pc + 1) % MEM_SIZE].byte;
	ret = insert_offset(proc, 2, direct);
	ft_memcpy(tmp, proc->op.p, sizeof(tmp));
	proc->op.p[0] = load_from_ram(vm, proc->pc + 2, proc->op.p[0]);
	proc->op.p[1] = load_from_ram(vm, proc->pc + 2 + tmp[0], proc->op.p[1]);
	if (tmp[0] == 2)
		proc->op.ind[0] = (flag & OP_RESTRICT)
			? load_from_ram(vm, proc->pc + proc->op.p[0] % IDX_MOD, 4)
			: load_from_ram(vm, proc->pc + proc->op.p[0], 4);
	if (tmp[1] == 2)
		proc->op.ind[1] = (flag & OP_RESTRICT)
			? load_from_ram(vm, proc->pc + proc->op.p[1] % IDX_MOD, 4)
			: load_from_ram(vm, proc->pc + proc->op.p[1], 4);
	proc->next_pc = (proc->pc + 2 + ret) % MEM_SIZE;
}

void		op_load_three(t_vm *vm, t_process *pr, uint16_t cycle, uint8_t flag)
{
	int	ret;
	int	direct;
	int	tmp[3];

	direct = (flag & OP_DIRECT_2) ? 2 : 4;
	pr->cycle_to_wait = cycle - 1;
	pr->op.ocp = vm->ram[(pr->pc + 1) % MEM_SIZE].byte;
	ret = insert_offset(pr, 3, direct);
	ft_memcpy(tmp, pr->op.p, sizeof(tmp));
	pr->op.p[0] = load_from_ram(vm, pr->pc + 2, pr->op.p[0]);
	pr->op.p[1] = load_from_ram(vm, pr->pc + 2 + tmp[0], pr->op.p[1]);
	pr->op.p[2] = load_from_ram(vm, pr->pc + 2 + tmp[1] + tmp[0], pr->op.p[2]);
	if (tmp[0] == 2)
		pr->op.ind[0] = (flag & OP_RESTRICT)
			? load_from_ram(vm, pr->pc + pr->op.p[0] % IDX_MOD, 4)
			: load_from_ram(vm, pr->pc + pr->op.p[0], 4);
	if (tmp[1] == 2)
		pr->op.ind[1] = (flag & OP_RESTRICT)
			? load_from_ram(vm, pr->pc + pr->op.p[1] % IDX_MOD, 4)
			: load_from_ram(vm, pr->pc + pr->op.p[1], 4);
	if (tmp[2] == 2)
		pr->op.ind[2] = (flag & OP_RESTRICT)
			? load_from_ram(vm, pr->pc + pr->op.p[2] % IDX_MOD, 4)
			: load_from_ram(vm, pr->pc + pr->op.p[2], 4);
	pr->next_pc = (pr->pc + 2 + ret) % MEM_SIZE;
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
