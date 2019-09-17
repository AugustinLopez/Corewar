/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:51:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/17 11:38:44 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		failure_condition(t_process *process, t_bool r_to_r)
{
	process->carry = 0;
	if (process->op->p[0] > REG_NUMBER || process->op->p[0] <= 0)
		return (FAILURE);
	if (r_to_r && (process->op->p[1] > REG_NUMBER || process->op->p[1] <= 0))
		process->carry = 0;
		return (FAILURE);
	process->carry = 1;
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
}

int		op_st(t_vm *vm, t_process *process)
{
	t_bool	reg_to_reg;
	size_t	addr;

	reg_to_reg = (((process->ocp >> 4) & 0x3) == REG_CODE) ? TRUE : FALSE;
	addr = (process->pc + (process->op->[1] % IDX_MOD)) % MEM_SIZE;
	process->pc = (reg_to_reg == TRUE)
		? (process->pc + 5) % MEM_SIZE : (process->pc + 7) % MEM_SIZE;
	if (failure_condition(process, reg_to_reg) == FAILURE)
		return (FAILURE);
	load_data(vm, process, reg_to_reg, addr);
	process->op->op = 0;
	return (SUCCESS);
}
