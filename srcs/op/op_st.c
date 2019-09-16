/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:51:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/16 16:05:27 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

t_bool	second_is_register(t_vm *vm, t_process *process)
{
	if (((process->ocp >> 4) & 0x3) == REG_CODE)
		return (TRUE);
	return (FALSE);
}

void	modify_pc(t_process *process, t_bool *reg_to_reg)
{
	if (reg_to_reg == TRUE)
		process->pc = (process->pc + 5) % MEM_SIZE;
	else
		process->pc = (process->pc + 7) % MEM_SIZE;
}

int		failure_condition(t_process *process)
{
	if (process->op->p[0] > REG_NUMBER || process->op->p[0] <= 0)
	{
		process->carry = 0;
		return (FAILURE);
	}
	if (reg_to_reg
			&& (process->op->p[1] > REG_NUMBER || process->op->p[1] <= 0))
	{
		process->carry = 0;
		return (FAILURE);
	}
	return (SUCCESS);
}

void	load_data(t_vm *vm, t_process *process, t_bool reg_to_reg, size_t addr)
{
	int		mask;
	int		decal;
	int		i;

	if (reg_to_reg)
		process->r[process->op->p[1] - 1] = process->r[process->op->p[0] - 1];
	else
	{
		i = 0;
		mask = 0xC0;
		decal = 6;
		while (i++ < REG_SIZE)
		{
			vm->ram[addr]->byte = (process->r[reg] & mask) >> decal;
			addr = (addr + 1) % MEM_SIZE;
			mask >>= 2;
			decal -= 2;
		}
		process->carry = 1;
}

int		op_st(t_vm *vm, t_process *process)
{
	t_bool	reg_to_reg;
	size_t	addr;

	reg_to_reg = second_is_register(vm, process);
	addr = (process->pc + (process->op->[1] % IDX_MOD)) % MEM_SIZE;
	modify_pc(process, reg_to_reg);
	if (failure_condition(process, reg_to_reg) == FAILURE)
		return (FAILURE);
	load_data(vm, process, reg_to_reg, addr);
	process->op->op = 0;
	return (SUCCESS);
}
