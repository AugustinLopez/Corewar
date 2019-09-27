/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:51:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/27 17:24:11 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_live(t_vm *vm, t_process *process)
{
	int	i;

	if (vm->cycle_to_die == 0)
		return (FAILURE);
	process->op.p[0] = load_from_ram(vm, (process->pc + 1) % MEM_SIZE, 4);
	++vm->live_since_check;
	process->next_pc = (process->pc + 5) % MEM_SIZE;
	process->alive = TRUE;
	i = 0;
	while (i < vm->player_total)
	{
		if (vm->player[i].id == process->op.p[0])
		{
			++(vm->player[i].live_since_check);
			++(vm->player[i].live_total);
			(vm->player[i].live_last) = vm->cycle_total - 1;
			vm->last_player_alive = vm->player[i].id;
			/*ft_printf("%sP - %zu%s > Player (\"%s\") is alive\n",
					FT_BOLD, process->process_id, FT_EOC, vm->player[i].name);*/
			return (SUCCESS);
		}
		++i;
	}
	return (FAILURE);
}
