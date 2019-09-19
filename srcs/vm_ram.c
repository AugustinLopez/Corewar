/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ram.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/19 14:11:46 by aulopez          ###   ########.fr       */
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
		ft_printf("%s%sPlayer %u%s - ",
			FT_UNDER, FT_BOLD, i + 1, FT_EOC);
		ft_printf("%sID:%s %d - ",
			FT_UNDER, FT_EOC, (vm->player[i]).id);
		ft_printf("%sName:%s %s- \n",
			FT_UNDER, FT_EOC, (vm->player[i]).name);
		//ft_printf("\t%sLive now:%s\t %zu\n",
		//	FT_UNDER, FT_EOC, (vm->player[i]).live_since_check);
		ft_printf("\t%sLive total:%s\t %zu\n",
			FT_UNDER, FT_EOC, (vm->player[i]).live_total);
		ft_printf("\t%sAlive ?%s\t\t %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).still_alive ? "Yes" : "No");
		++i;
	//	ft_putchar('\n');
	}
}

void	dump_memory(t_vm *vm, size_t x)
{
	size_t	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (vm->ram[i].process == TRUE)
			ft_putstr(FT_REV);
		if (vm->ram[i].cycle_last > 0
			&& vm->ram[i].cycle_last + 10 > vm->cycle_total)
				ft_printf("%s%s", FT_BOLD, FT_DIM);
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
	print_player_info(vm);
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
