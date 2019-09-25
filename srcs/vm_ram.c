/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ram.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/25 16:19:03 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <unistd.h>

void	print_player_info(t_vm *vm)
{
	uint8_t	i;

	i = 0;
	while (i < vm->player_total)
	{
		ft_printf("%s%sPlayer %u%s\n",
			FT_UNDER, FT_BOLD, i + 1, FT_EOC);
		ft_printf("\t       %sID:%s  %d\n",
			FT_UNDER, FT_EOC, (vm->player[i]).id);
		ft_printf("\t     %sName:%s  %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).name);
		ft_printf("\t%s Live now:%s  %zu\n",
			FT_UNDER, FT_EOC, (vm->player[i]).live_since_check);
		ft_printf("\t%sLive last:%s  %zu\n",
			FT_UNDER, FT_EOC, (vm->player[i]).live_last);
		++i;
	}
}

void	print_info(int cycle, size_t i, t_vm *vm)
{
	if (cycle == 0)
	{
		if (vm->ram[i].process == TRUE)
			ft_putstr(FT_REV);
		if (vm->ram[i].cycle_last > 0
			&& vm->ram[i].cycle_last + 20 > vm->cycle_total)
				ft_printf("%s%s", FT_BOLD, FT_DIM);
		if (vm->ram[i].player_last == vm->player[0].id)
			ft_putstr(FT_LGREEN);
		else if (vm->ram[i].player_last == vm->player[1].id)
			ft_putstr(FT_LBLUE);
		else if (vm->ram[i].player_last == vm->player[2].id)
			ft_putstr(FT_LRED);
		else if (vm->ram[i].player_last == vm->player[3].id)
			ft_putstr(FT_LYELLOW);
		ft_printf("%02x%s", vm->ram[i].byte, FT_EOC);
		return ;
	}
	ft_printf("%s%sCurrent process:%s %zu\n\n", FT_UNDER, FT_BOLD, FT_EOC, vm->process_total);
	print_player_info(vm);
}

void	dump_memory(t_vm *vm, size_t x, t_bool pretty)
{
	size_t	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % x == 0)
			ft_printf("0x%.4x : ", i);
		if (pretty == FALSE)
			ft_printf("%02x", vm->ram[i].byte);
		else
			print_info(0, i, vm);
		if (i % x == x - 1)
			write(1, " \n", 2);
		else
			write(1, " ", 1);
		++i;
	}
	if (pretty == TRUE)
		print_info(1, 0, vm);
}

void	write_in_ram(t_vm *vm, t_process *proc, int addr, int number)
{
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	vm->ram[(addr + 0) % MEM_SIZE].byte = (number >> 24) & 0xff;
	vm->ram[(addr + 0) % MEM_SIZE].write_total++;
	vm->ram[(addr + 0) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 0) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 1) % MEM_SIZE].byte = (number >> 16) & 0xff;
	vm->ram[(addr + 1) % MEM_SIZE].write_total++;
	vm->ram[(addr + 1) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 1) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 2) % MEM_SIZE].byte = (number >> 8) & 0xff;;
	vm->ram[(addr + 2) % MEM_SIZE].write_total++;
	vm->ram[(addr + 2) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 2) % MEM_SIZE].player_last = proc->player_id;
	vm->ram[(addr + 3) % MEM_SIZE].byte = number & 0xff;
	vm->ram[(addr + 3) % MEM_SIZE].write_total++;
	vm->ram[(addr + 3) % MEM_SIZE].cycle_last = vm->cycle_total;
	vm->ram[(addr + 3) % MEM_SIZE].player_last = proc->player_id;
}

int		load_from_ram(t_vm *vm, size_t pc, int nbr)
{
	int		ret;
	short	ret2;

	pc %= MEM_SIZE;
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

int		load_ind(t_vm *vm, t_process *proc, int addr, uint8_t flag)
{
	int	ret;

	if (flag & OP_IDX)
		addr = (proc->pc + addr % IDX_MOD) % MEM_SIZE;
	else
		addr = (proc->pc + addr) % MEM_SIZE;
	if (addr < 0)
		addr = MEM_SIZE + addr % MEM_SIZE;
	ret = load_from_ram(vm, addr, (flag & OP_IND) ? 2 : 4);
	return (ret);
}

int		load_offset(t_vm *vm, t_process *proc, int i, uint8_t flag)
{
	int	ocp;
	int	tmp;

	ocp = ((proc->op.ocp) >> ((4 - i) * 2)) & 0x3;
	if (ocp == REG_CODE)
		proc->op.p[i - 1] = 1;
	else if (ocp == DIR_CODE)
		proc->op.p[i - 1] = (flag & OP_DIR) ? 2 : 4;
	else if (ocp == IND_CODE)
		proc->op.p[i - 1] = 2;
	else
		proc->op.p[i - 1] = 0;
	tmp = proc->op.p[i - 1];
	proc->op.p[i - 1] = load_from_ram(vm, (proc->next_pc + 1) % MEM_SIZE
			, proc->op.p[i - 1]);
	proc->next_pc = (proc->next_pc + tmp) % MEM_SIZE;
	return (ocp);
}

t_bool	load_from_ocp(t_vm *vm, t_process *proc, int nbr_arg, uint8_t flag)
{
	int		i;
	int		ocp;
	t_bool	ret;

	ret = TRUE;
	i = 0;
	proc->op.ocp = load_from_ram(vm, (proc->pc + 1) % MEM_SIZE, 1);
	proc->next_pc = proc->pc + 1;
	while (i++ < nbr_arg)
	{
		ocp = load_offset(vm, proc, i, flag);
		if (ocp == 0 || (ocp == REG_CODE
				&& !(0 < proc->op.p[i - 1] && proc->op.p[i - 1] <= REG_NUMBER)))
			ret = FALSE;
		if (ocp == IND_CODE)
			proc->op.ind[i - 1] = load_ind(vm, proc, proc->op.p[i - 1], flag);
	}
	proc->next_pc = (proc->next_pc + 1) % MEM_SIZE;
	return (ret);
}
