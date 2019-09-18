/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_XXX_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:11:12 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/18 12:50:06 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

/*
** !!! Pour l'instant : AUCUNE MODIF FAITE SUR l'OP EN AUCUN CAS !!!
*/

// op = 2 or op = 13
int	op_ld_lld_load(t_vm *vm, t_process *proc)
{
	size_t	m; // = mask byte position

	proc->cycle_to_wait = proc->op == 13 ? 10 - 1: 5 - 1;
	m = (proc->pc + 1) % MEM_SIZE;
	proc->op.offset = get_offset(proc->op.op, vm->ram[m].byte, proc);
	if (vm->ram[m].byte == 0xD0 || vm->ram[m].byte == 0x90)
	{
		m += proc->op.p[0];
		proc->op.p[0] == load_op(vm, proc, proc->op.p[0], m % MEM_SIZE);
		m += proc->op.p[1];
		proc->op.p[1] == load_op(vm, proc, proc->op.p[1], m % MEM_SIZE);
		proc->valid_ocp = TRUE;
		return (SUCCESS);
	}
	proc->valid_ocp = FALSE;
	return (FAILURE);
}

// op = 3
int	op_st_load(t_vm *vm, t_process *proc)
{
	size_t	m;

	proc->cycle_to_wait = 5 - 1;
	m = (proc->pc + 1) % MEM_SIZE;
	proc->op.ocp = get_ocp(proc->op.op, vm->ram[m].byte);
	if (proc->op.ocp == 2 && vm->ram[m].byte == 0x50)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 2) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 3 && vm->ram[m].byte == 0x70)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, (m + 2) % MEM_SIZE);
		return (SUCCESS);
	}
	return (FAILURE);
}

// op = 4 or op = 5
int	op_add_sub_load(t_vm *vm, t_process *proc)
{
	size_t	m;

	proc->cycle_to_wait = 10 - 1;
	m = (proc->pc + 1) % MEM_SIZE;
	proc->op.ocp = get_ocp(proc->op.op, vm->ram[m].byte);
	if (proc->op.ocp == 3 && vm->ram[m].byte == 0x54)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 3) % MEM_SIZE);
		return (SUCCESS);
	}
	return (FAILURE);
}

// op = 6 or op = 7 or op = 8
int	op_and_or_xor_load(t_vm *vm, t_process *proc)
{
	size_t m;

	proc->cylce_to_wait = 6 - 1;
	m = (proc->pc + 1) % MEM_SIZE;
	proc->op.ocp = get_ocp(proc->op.op, vm->ram[m].byte);
	if (proc->op.ocp == 3 && vm->ram[m].byte == 0x54)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 3) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 4 && vm->ram[m].byte == 0x74)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 4) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 4 && vm->ram[m].byte == 0xD4)
	{
		proc->op.p[0] == load_op(vm, proc, 2, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 3) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 4) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 5 && vm->ram[m].byte == 0xF4)
	{
		proc->op.p[0] == load_op(vm, proc, 2, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, ((m + 3) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 5) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 6 && vm->ram[m].byte == 0x64)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 4, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 6) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 6 && vm->ram[m].byte == 0x94)
	{
		proc->op.p[0] == load_op(vm, proc, 4, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 5) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 6) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 7 && vm->ram[m].byte == 0xB4)
	{
		proc->op.p[0] == load_op(vm, proc, 4, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, (m + 5) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 7) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 7 && vm->ram[m].byte == 0xE4)
	{
		proc->op.p[0] == load_op(vm, proc, 2, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 4, (m + 3) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 7) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 9 && vm->ram[m].byte == 0xA4)
	{
		proc->op.p[0] == load_op(vm, proc, 4, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 4, (m + 5) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 9) % MEM_SIZE);
		return (SUCCESS);
	}
	return (FAILURE);
}

// op = 9
int	op_zjmp_load(t_vm *vm, t_process *proc)
{
	proc->cylce_to_wait = 20 - 1;
	proc->op.p[0] = load_op(vm, proc, 2, ((proc->pc + 1) % MEM_SIZE);
	return (SUCCESS);
}

// op = 10 ou op = 14
int	op_ldi_lldi_load(t_vm *vm, t_process *proc)
{
	size_t	m;

	proc->cylce_to_wait = proc->op == 14 ? 50 - 1: 25 - 1;
	m = (proc->pc + 1) % MEM_SIZE;
	proc->op.ocp = get_ocp(proc->op.op, vm->ram[m].byte);
	if (proc->op.ocp == 3 && vm->ram[m].byte == 0x54)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 3) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 4 && vm->ram[m].byte == 0x64)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 4) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 4 && (vm->ram[m].byte == 0x94
				|| vm->ram[m].byte == 0xD4))
	{
		proc->op.p[0] == load_op(vm, proc, 2, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 3) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 4) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 5 && (vm->ram[m].byte == 0xA4
			|| vm->ram[m].bye == 0xE4))
	{
		proc->op.p[0] == load_op(vm, proc, 2, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, (m + 3) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 5) % MEM_SIZE);
		return (SUCCESS);
	}
	return (FAILURE);
}


//op = 11
int	op_sti_load(t_vm *vm, t_process *proc)
{
	size_t	m;
	proc->cylce_to_wait = 25 - 1;
	m = (proc->pc + 1) % MEM_SIZE;
	proc->op.ocp = get_ocp(proc->op.op, vm->ram[m].byte);
	if (proc->op.ocp == 3 && vm->ram[m].byte == 0x54)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 3) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 4 && vm->ram[m].byte == 0x58)
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 1, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 2, (m + 3) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 4 && (vm->ram[m].byte == 0x64
				|| vm->ram[m].byte == 0x74))
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 1, (m + 4) % MEM_SIZE);
		return (SUCCESS);
	}
	else if (proc->op.ocp == 5 && (vm->ram[m].byte == 0x68
			|| vm->ram[m].bye == 0x78))
	{
		proc->op.p[0] == load_op(vm, proc, 1, (m + 1) % MEM_SIZE);
		proc->op.p[1] == load_op(vm, proc, 2, (m + 2) % MEM_SIZE);
		proc->op.p[2] == load_op(vm, proc, 2, (m + 4) % MEM_SIZE);
		return (SUCCESS);
	}
	return (FAILURE);
}

// op = 12
int	op_fork_load(t_vm *vm, t_process *proc)
{
	proc->cylce_to_wait = 800 - 1;
	proc->op.p[0] = load_op(vm, proc, 2, ((proc->pc + 1) % MEM_SIZE);
	return (SUCCESS);
}

// op = 15
int	op_lfork_load(t_vm *vm, t_process *proc)
{
	proc->cylce_to_wait = 1000 - 1;
	proc->op.p[0] = load_op(vm, proc, 2, ((proc->pc + 1) % MEM_SIZE);
	return (SUCCESS);
}

// op = 16
int	op_aff_load(t_vm *vm, t_process *proc)
{
	proc->cylce_to_wait = 2 - 1;
	proc->op.p[0] = load_op(vm, proc, 1, ((proc->pc + 1) % MEM_SIZE);
	return (SUCCESS);
}
