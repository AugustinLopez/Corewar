/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:51:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/10/14 18:14:24 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

static inline void liveloop(t_vm *vm, t_process *process, int i)
{
	++(vm->player[i].live_since_check);
	++(vm->player[i].live_total);
	(vm->player[i].live_last) = vm->cycle_total - 1;
	vm->last_player_alive = vm->player[i].id;
	if (vm->flag & FLAG_LIKE_PDF)
		ft_printf("%sP - %zu%s > Player %d (\"%s\") is alive\n", FT_BOLD
				, process->process_id, FT_EOC, vm->player[i].id
				, vm->player[i].name);
}

int					op_live(t_vm *vm, t_process *process)
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
			liveloop(vm, process, i);
			return (SUCCESS);
		}
		++i;
	}
	return (FAILURE);
}
