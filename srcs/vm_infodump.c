/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_infodump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/26 10:58:53 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <unistd.h>

static inline void	print_player_info(t_vm *vm)
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

static inline void	print_info(int cycle, size_t i, t_vm *vm)
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
	ft_printf("%s%sCurrent process:%s %zu\n\n"
			, FT_UNDER, FT_BOLD, FT_EOC, vm->process_total);
	print_player_info(vm);
}

void				dump_memory(t_vm *vm, size_t x, t_bool pretty)
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
