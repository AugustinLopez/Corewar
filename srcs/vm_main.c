/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/18 13:05:08 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

/*const t_op				g_op_table[17] = {
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};
*/

static int insert_offset(uint8_t ocp, t_process *proc, int nb_arg, int direct)
{
	int		i;
	uint8_t	temp;
	int		sum;

	i = 0;
	sum = 0;
	while (i < nb_arg)
	{
		temp = (ocp >> ((3 - i) * 2)) & 0x3;
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

int	get_offset(uint8_t op, uint8_t ocp, t_process *proc)
{
	if (op == 0 || op > 16)
		return (1);
	if (op == 1)
		return (5);
	if (op == 9 || op == 12 || op == 15)
		return (3);
	if (op == 16)
		return (2);
	if (op == 2 || op == 3 || op == 13) //2 ARG, DIR == 4
		return (insert_offset(ocp, proc, 2, 4));
	if (4 <= op && op <= 8) //3 arg, dir == 4
		return (insert_offset(ocp, proc, 3, 4));
	if (op == 10 || op == 11 || op == 14) //3arg, dir == 2
		return (insert_offset(ocp, proc, 3, 2));
	return (0);
}



int	load_new_process(t_vm *vm, t_process *proc)
{
	vm->ram[proc->pc].process = FALSE;
	proc->pc = (proc->pc + 1) % MEM_SIZE;
	proc->op.op = vm->ram[proc->pc].byte;
	if (proc->op.op == 1)
		return (op_live_load(vm, proc));
	return (FAILURE);
}


int	analyze_process(t_vm *vm, t_process *proc)
{
	if (proc->cycle_to_wait)
	{
		--(proc->cycle_to_wait);
		return (SUCCESS);
	}
	if (proc->op.op == 0)
		return (load_new_process(vm, proc));
	if (proc->op.op == 1)
		return (op_live_proceed(vm, proc));
	return (load_new_process(vm, proc));
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

int	main(int argc, char **argv)
{
	t_vm		vm;
	char		*buff;

	if (parser(&vm, argc, argv) == FAILURE)
		return (-1);
	dump_memory(&vm, 64);
	while (ft_gnl(1, &buff, 0) > 0)
	{
		ft_printf("%sCycle %zu%s:\n", FT_UNDER, ++vm.cycle_total, FT_EOC);
		(void)proceed_cycle(&vm);
		dump_memory(&vm, 64);
		free(buff);
		buff = 0;
	}
	free(buff);
	buff = 0;
	//dump_memory(&vm, 64);
	access_all_players(&vm);
	access_all_processes(&vm);
	free_all_players(&vm);
	free_all_processes(&vm);
	return (0);
}
