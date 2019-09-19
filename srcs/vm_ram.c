/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_ram.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/19 11:34:44 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <unistd.h>

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
