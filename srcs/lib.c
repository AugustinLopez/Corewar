/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/12 12:52:13 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

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
	while (i < vm->player_total)
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
		ft_printf("\t%sID:%s\t\t %u\n",
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
		ft_printf("\t%sSpawned by:%s\t %u\n",
			FT_UNDER, FT_EOC, tmp->player_id);
		ft_printf("\t%sRegister:%s\n", FT_UNDER, FT_EOC);
		while (i < REG_NUMBER)
		{
			ft_printf("%s\t  R%-2u%s -> %u\n",
				FT_BOLD, i + 1, FT_EOC, tmp->r[i]);
			++i;
		}
		ft_printf("\t%sOperation%s:\t ", FT_UNDER, FT_EOC);
		ft_printf("%02x %02x %02x %02x %02x %02x\n", tmp->op.id,
			tmp->op.encoding, tmp->op.p[0], tmp->op.p[1], tmp->op.p[2], 
			tmp->op.p[3]);
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

void	dump_memory(t_vm *vm, int x)
{
	size_t	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % x == x - 1)
			ft_printf("%02x\n", vm->ram[i].byte);
		else
			ft_printf("%02x ", vm->ram[i].byte);
		++i;
	}
}
/*
int	main(void)
{
	t_vm	vm;
	char	*n1 = ft_strdup("test1");
	char	*n2 = ft_strdup("test2");
	char	*c1 = ft_strdup("Hello World");
	char	*c2 = ft_strdup("");

	ft_bzero(&vm, sizeof(vm));
	if (init_player(&vm, 100, n1, c1) == SUCCESS)
	{
		if (init_player(&vm, 2, n2, c2) == SUCCESS)
		{
			if (init_process(&vm) == SUCCESS)
				create_process(&vm, 15, vm.process->player_id);
		}
	}
	access_all_players(&vm);
	access_all_processes(&vm);
	dump_memory(&vm, 64);
	free_all_players(&vm);
	free_all_processes(&vm);
	ft_printf("Sizeof(vm) = %zu\n", sizeof(vm));
	return (0);
}*/
