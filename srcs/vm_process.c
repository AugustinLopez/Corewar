/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/25 15:04:29 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

static void	print_reg_content(t_process *tmp)
{
	uint8_t	i;

	i = 0;
	ft_printf("\t%sRegister:%s\n", FT_UNDER, FT_EOC);
	while (i < REG_NUMBER)
	{
		ft_printf("%s\t  R%-2u%s -> %d\n", FT_BOLD, i + 1, FT_EOC, tmp->r[i]);
		++i;
	}
}

void		print_all_processes(t_vm *vm)
{
	t_process	*tmp;

	tmp = vm->process;
	while (tmp)
	{
		ft_printf("%s%sProcess %u:%s\n",
			FT_UNDER, FT_BOLD, tmp->process_id, FT_EOC);
		ft_printf("\t%sSpawned by:%s\t %d\n",
			FT_UNDER, FT_EOC, tmp->player_id);
		print_reg_content(tmp);
		ft_printf("\t%sOperation%s:\t ", FT_UNDER, FT_EOC);
		ft_printf("%02x %02x %02x %02x %02x\n", tmp->op.op,
			tmp->op.ocp, tmp->op.p[0], tmp->op.p[1], tmp->op.p[2]);
		ft_printf("\t%sWait for:%s\t %zu\n",
			FT_UNDER, FT_EOC, tmp->cycle_to_wait);
		ft_printf("\t%sPC:%s\t\t %zu\n",
			FT_UNDER, FT_EOC, tmp->pc);
		ft_printf("\t%sCarry:%s\t\t %u\n",
			FT_UNDER, FT_EOC, tmp->carry);
		tmp = tmp->next;
		ft_putchar('\n');
	}
}

void		free_all_processes(t_vm *vm)
{
	t_process	*tmp;

	tmp = vm->process;
	while (tmp)
	{
		vm->process = tmp;
		tmp = tmp->next;
		free(vm->process);
	}
}

t_process		*free_process(t_vm *vm, t_process *proc)
{
	t_process *tmp;

	vm->process_total--;
	if (proc)
		vm->ram[proc->pc % MEM_SIZE].process = FALSE;
	if (vm->process == proc)
	{
		vm->process = vm->process->next;
		if (vm->process)
			vm->process->prev = NULL;
		free(proc);
		return (vm->process);
	}
	else
	{
		tmp = proc->next;
		if (proc->prev)
			proc->prev->next = proc->next;
		if (proc->next)
			proc->next->prev = proc->prev;
		free(proc);
		return (tmp);
	}
}

int			create_process(t_vm *vm, size_t pc, int player_id)
{
	t_process *tmp;

	if (!(tmp = (t_process *)malloc(sizeof(*tmp))))
		return (FAILURE);
	++vm->process_total;
	ft_bzero(tmp, sizeof(*tmp));
	tmp->pc = pc % MEM_SIZE;
	tmp->next_pc = tmp->pc;
	tmp->player_id = player_id;
	tmp->process_id = ++vm->process_index;
	tmp->next = vm->process;
	if (vm->process)
		vm->process->prev = tmp;
	vm->process = tmp;
	return (SUCCESS);
}

int			create_process_bis(t_vm *vm, size_t pc, int player_id, t_process *proc)
{
	t_process *tmp;

	if (!(tmp = (t_process *)malloc(sizeof(*tmp))))
		return (FAILURE);
	++vm->process_total;
	ft_bzero(tmp, sizeof(*tmp));
	tmp->pc = pc % MEM_SIZE;
	tmp->next_pc = tmp->pc;
	tmp->player_id = player_id;
	tmp->process_id = ++vm->process_index;
	tmp->next = proc->next;
	if (tmp->next)
		tmp->next->prev = tmp;
	tmp->prev = proc;
	proc->next = tmp;
	return (SUCCESS);
}
