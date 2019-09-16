/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:51:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/16 15:48:25 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

size_t	load_address(t_process *process, t_bool long_option)
{
	if (long_option == FALSE)
		return ((process->pc + process->op->[0] % IDX_MOD) % MEM_SIZE);
	return ((process->pc + process->op->[0]) % MEM_SIZE);
}

void	modify_pc(t_process *process)
{
	if ((process->ocp >> 6) == DIR_CODE)
		process->pc = (process->pc + 7) % MEM_SIZE;
	else
		process->pc = (process->pc + 5) % MEM_SIZE;
}

int		failure_condition(t_process *process)
{
	if (process->op->p[1] > REG_NUMBER || process->op->p[1] <= 0)
	{
		process->carry = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	load_in_register(t_vm *vm, t_process *process, size_t addr)
{
	int		reg;
	int		i;

	i = 0;
	reg = process->op->p[1] - 1;
	process->r[reg] = 0;
	while (i++ < REG_SIZE)
	{
		process->r[reg] = (process->r[reg] << 8) + vm->ram[addr]->byte;
		addr = (addr + 1) % MEM_SIZE;
	}
	process->carry = 1;
}

int		op_ld(t_vm *vm, t_process *process, t_bool long_option)
{
	size_t	addr;

	addr = load_address(process, long_option);
	modify_pc(process);
	if (failure_condition(process) == FAILURE)
		return (FAILURE);
	load_in_register(vm, process, addr);
	process->op->op = 0;
	return (SUCCESS);
}
