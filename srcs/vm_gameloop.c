/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_gameloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 12:26:44 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/26 14:35:09 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

void				load_process(t_vm *vm, t_process *proc)
{
	static const int cycle_to_wait[17] = {0
			, 10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

	proc->op.op = vm->ram[proc->pc].byte;
	if (1 <= proc->op.op && proc->op.op <= 16)
		proc->cycle_to_wait = cycle_to_wait[proc->op.op] - 1;
	else
	{
		proc->op.op = 0;
		proc->next_pc = (proc->pc + 1) % MEM_SIZE;
	}
	if (vm->cycle_total == 1)
		proc->cycle_to_wait++;
}

static inline int	analyze_process(t_vm *vm, t_process *proc)
{
	static int (*fun_ptr[17])(t_vm *, t_process *) = {0
			, *op_live, *op_ld_lld, *op_st, *op_arithmetic, *op_arithmetic
			, *op_binary, *op_binary, *op_binary, *op_zjmp, *op_ldi_lldi
			, *op_sti, *op_fork_lfork, *op_ld_lld, *op_ldi_lldi
			, *op_fork_lfork, *op_aff};

	if (proc->op.op == 0)
		load_process(vm, proc);
	if (proc->cycle_to_wait)
	{
		--(proc->cycle_to_wait);
		return (SUCCESS);
	}
	if (1 <= proc->op.op && proc->op.op <= 16)
		(fun_ptr[proc->op.op])(vm, proc);
	proc->op.op = 0;
	vm->ram[proc->pc].process = FALSE;
	vm->ram[proc->next_pc].process = TRUE;
	proc->pc = proc->next_pc;
	return (0);
}

static inline int	kill_process(t_vm *vm)
{
	t_process	*proc;

	proc = vm->process;
	while (proc)
	{
		if (proc->alive == FALSE)
			proc = free_process(vm, proc);
		else
		{
			proc->alive = FALSE;
			proc = proc->next;
		}
	}
	if (vm->process == NULL)
		return (0);
	if (vm->live_since_check >= NBR_LIVE || vm->max_check > MAX_CHECKS - 1)
		vm->cycle_to_die -= (vm->cycle_to_die <= CYCLE_DELTA)
				? vm->cycle_to_die : CYCLE_DELTA;
	else
		vm->max_check++;
	vm->cycle_since_check = 0;
	vm->live_since_check = 0;
	return (1);
}

int					gameloop(t_vm *vm)
{
	t_process	*proc;

	++(vm->cycle_total);
	if (vm->cycle_since_check++ >= vm->cycle_to_die - 1)
		if (kill_process(vm) == 0)
			return (0);
	proc = vm->process;
	while (proc)
	{
		(void)analyze_process(vm, proc);
		proc = proc->next;
	}
	proc = vm->process;
	if (vm->min_wait == 0)
		vm->min_wait = 1001;
	while (proc)
	{
		vm->ram[proc->pc].process = TRUE;
		proc = proc->next;
	}
	if (vm->cycle_to_die == 0)
		return (0);
	return (1);
}
