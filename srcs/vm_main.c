/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/23 12:00:07 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

int	analyze_process(t_vm *vm, t_process *proc)
{
	if (proc->cycle_to_wait)
	{
		--(proc->cycle_to_wait);
		return (SUCCESS);
	}
	if (proc->op.op == 9)
		op_zjmp(proc);
	else if (proc->op.op == 1)
		op_live(vm, proc);
	else if (proc->op.op == 2 || proc->op.op == 13)
		op_ld_lld(proc);
	else if (proc->op.op == 3)
		op_st(vm, proc);
	else if (proc->op.op == 12 || proc->op.op == 15)
		op_fork_lfork(vm, proc);
	else if (proc->op.op == 4 || proc->op.op == 5)
		op_arithmetic(proc);
	else if (6 <= proc->op.op && proc->op.op <= 8)
		op_binary(proc);
	else if (proc->op.op == 10 || proc->op.op == 14)
		op_ldi_lldi(vm, proc);
	else if (proc->op.op == 11)
		op_sti(vm, proc);
	else if (proc->op.op == 16)
		op_aff(proc);
	vm->ram[proc->pc].process = FALSE;
	vm->ram[proc->next_pc].process = TRUE;
	proc->pc = proc->next_pc;
	proc->op.op = vm->ram[proc->pc].byte;
	load_process(vm, proc);
	return (0);
}

int	proceed_cycle(t_vm *vm)
{
	t_process *proc;

	proc = vm->process;
	while (proc)
	{
		(void)analyze_process(vm, proc);
		proc = proc->next;
	}
	proc = vm->process;
	while (proc)
	{
		vm->ram[proc->pc].process = TRUE;
		proc = proc->next;
	}
	return (0);
}

int	introduction(t_vm *vm)
{
	int	i;

	ft_printf("Introducing contestants...\n");
	i = 0;
	while (i++ < vm->player_total)
	{
		ft_printf("* Player %d, ", i);
		if (vm->player[i - 1].weight < 2)
			ft_printf("weighing %d byte, ", vm->player[i - 1].weight);
		else
			ft_printf("weighing %d bytes, ", vm->player[i - 1].weight);
		if ((vm->player[i - 1].name)[0])
			ft_printf("\"%s\" ", vm->player[i - 1].name);
		else
			ft_printf("\"\" ");
		if ((vm->player[i - 1].comment)[0])
			ft_printf("(\"%s\") !\n", vm->player[i - 1].comment);
		else
			ft_printf("(\"\") !\n");
	}
	return (SUCCESS);
}

int	corewar(t_vm *vm)
{
	size_t	cycle;

	introduction(vm);
	if (vm->cycle_to_dump == 0) //infinite, play to end
		return (1);
	cycle = 0;
	while (cycle++ <= vm->cycle_to_dump)
		proceed_cycle(vm);
	dump_memory(vm, 64);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_vm		vm;
	char		*buff;

	(void)buff;
	if (parser(&vm, argc, argv) == FAILURE)
		return (-1);
	corewar(&vm);
	/*dump_memory(&vm, 64);
	while (ft_gnl(1, &buff, 0) > 0)
	{
		ft_printf("%sCycle %zu%s:\n", FT_UNDER, vm.cycle_total, FT_EOC);
		(void)proceed_cycle(&vm);
		dump_memory(&vm, 64);
		free(buff);
		buff = 0;
	}
	free(buff);
	buff = 0;
	dump_memory(&vm, 64);
	print_all_players(&vm);
	print_all_processes(&vm);*/
	free_all_players(&vm);
	free_all_processes(&vm);
	return (0);
}
