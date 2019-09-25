/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:51:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/25 16:42:39 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_live(t_vm *vm, t_process *process)
{
	int	i;

	process->op.p[0] = load_from_ram(vm, (process->pc + 1) % MEM_SIZE, 4);
	++vm->live_since_check;
	process->next_pc = (process->pc + 5) % MEM_SIZE;
	process->alive = TRUE;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->player[i].id == process->op.p[0])
		{
			++(vm->player[i].live_since_check);
			++(vm->player[i].live_total);
			(vm->player[i].live_last) = vm->cycle_total - 1;
			vm->last_player_alive = vm->player[i].id;
			return (SUCCESS);
		}
		++i;
	}
	return (FAILURE);
}
