/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/18 13:05:33 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

void	free_all_processes(t_vm *vm)
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

//create process also need to read the operation at PC

int		create_process(t_vm *vm, size_t pc, int player_id)
{
	t_process *tmp;

	if (!(tmp = (t_process *)malloc(sizeof(*tmp))))
		return (FAILURE);
	++vm->process_total;
	ft_bzero(tmp, sizeof(*tmp));
	tmp->pc = pc;
	tmp->player_id = player_id;
	tmp->process_id = ++vm->process_index;
	tmp->next = vm->process;
	if (vm->process)
		vm->process->prev = tmp;
	vm->process = tmp;
	return (SUCCESS);
}

int		init_process(t_vm *vm)
{
	size_t	pc;
	uint8_t	i;

	pc = 0;
	i = 0;
	while (i < vm->player_total)
	{
		if (create_process(vm, pc, (vm->player[i]).id) == FAILURE)
			return (FAILURE);
		pc += MEM_SIZE / vm->player_total;
		vm->process->r[0] = (vm->player[i]).id;
		++i;
	}
	return (SUCCESS);
}

int	init_player(t_vm *vm, int index, char *name, char *comment)
{
	uint8_t	i;

	i = 0;
	while (i < vm->player_total)
		if ((vm->player[i++]).id == index)
			return (FAILURE);
	++(vm->player_total);
	(vm->player[i]).id = index;
	(vm->player[i]).name = name;
	(vm->player[i]).comment = comment;
	(vm->player[i]).still_alive = TRUE;
	return (SUCCESS);
}

void	free_all_players(t_vm *vm)
{
	uint8_t	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if ((vm->player[i]).name)
			free((vm->player[i]).name);
		if ((vm->player[i]).comment)
			free((vm->player[i]).comment);
		++i;
	}
}

void	access_all_players(t_vm *vm)
{
	uint8_t	i;

	i = 0;
	while (i < vm->player_total)
	{
		ft_printf("%s%sPlayer %u:%s\n",
			FT_UNDER, FT_BOLD, i + 1, FT_EOC);
		ft_printf("\t%sID:%s\t\t %d\n",
			FT_UNDER, FT_EOC, (vm->player[i]).id);
		ft_printf("\t%sName:%s\t\t %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).name);
		ft_printf("\t%sComment:%s\t %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).comment);
		ft_printf("\t%sLive now:%s\t %zu\n",
			FT_UNDER, FT_EOC, (vm->player[i]).live_since_check);
		ft_printf("\t%sLive total:%s\t %zu\n",
			FT_UNDER, FT_EOC, (vm->player[i]).live_total);
		ft_printf("\t%sAlive ?%s\t\t %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).still_alive ? "Yes" : "No");
		++i;
		ft_putchar('\n');
	}
}

void	access_all_processes(t_vm *vm)
{
	t_process	*tmp;
	uint8_t		i;

	tmp = vm->process;
	while (tmp)
	{
		ft_printf("%s%sProcess %u:%s\n",
			FT_UNDER, FT_BOLD, tmp->process_id, FT_EOC);
		i = 0;
		ft_printf("\t%sSpawned by:%s\t %d\n",
			FT_UNDER, FT_EOC, tmp->player_id);
		ft_printf("\t%sRegister:%s\n", FT_UNDER, FT_EOC);
		while (i < REG_NUMBER)
		{
			ft_printf("%s\t  R%-2u%s -> %d\n",
				FT_BOLD, i + 1, FT_EOC, tmp->r[i]);
			++i;
		}
		ft_printf("\t%sOperation%s:\t ", FT_UNDER, FT_EOC);
		ft_printf("%02x %02x %02x %02x %02xx\n", tmp->op.op,
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

int		load_from_ram(t_vm *vm, size_t pc, int nbr)
{
	int		ret;
	short	ret2;

	if (nbr == 1)
		return (vm->ram[pc].byte);
	if (nbr == 2)
	{
		ret2 = vm->ram[pc].byte << 8;
		pc = (pc + 1) % MEM_SIZE;
		ret2 |= vm->ram[pc].byte;
		return (ret2);
	}
	ret = vm->ram[pc].byte << 24;
	pc = (pc + 1) % MEM_SIZE;
	ret |= vm->ram[pc].byte << 16;
	pc = (pc + 1) % MEM_SIZE;
	ret |= vm->ram[pc].byte << 8;
	pc = (pc + 1) % MEM_SIZE;
	ret |= vm->ram[pc].byte;
	return (ret);
}

void	dump_memory(t_vm *vm, size_t x)
{
	size_t	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->ram[i].process == TRUE)
			ft_putstr(FT_REV);
		if (vm->ram[i].player_last == vm->player[0].id)
			ft_putstr(FT_LRED);
		else if (vm->ram[i].player_last == vm->player[1].id)
			ft_putstr(FT_LBLUE);
		else if (vm->ram[i].player_last == vm->player[2].id)
			ft_putstr(FT_LGREEN);
		else if (vm->ram[i].player_last == vm->player[3].id)
			ft_putstr(FT_LYELLOW);
		ft_printf("%02x%s", vm->ram[i].byte, FT_EOC);
		if (i % x == x - 1)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		++i;
	}
}

int		load_op(t_vm *vm, t_process *process, int nbr, size_t pc)
{
	int		ret;
	short	ret2;
	size_t	addr;

	(void)process;
	addr = pc;
	if (nbr == 1)
		return (vm->ram[pc].byte);
	if (nbr == 2)
	{
		ret2 = vm->ram[addr].byte << 8;
		addr = (addr + 1) % MEM_SIZE;
		ret2 |= vm->ram[addr].byte;
		return (ret2);
	}
	ret = vm->ram[addr].byte << 24;
	addr = (addr + 1) % MEM_SIZE;
	ret |= vm->ram[addr].byte << 16;
	addr = (addr + 1) % MEM_SIZE;
	ret |= vm->ram[addr].byte << 8;
	addr = (addr + 1) % MEM_SIZE;
	ret |= vm->ram[addr].byte;
	return (ret);
}
