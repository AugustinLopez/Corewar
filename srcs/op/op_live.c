/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 13:51:34 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/16 14:57:53 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		op_live(t_vm *vm, t_process *process)
{
	int	i;

	i = 0;
	process->pc = (process->pc + 5) % MEM_SIZE;
	while (i < MAX_PLAYER)
	{
		if (vm->player[i]->id == process->p[0])
		{
			if (vm->player[i]->still_alive == FALSE)
				return (FAILURE);
			++(vm->player[i]->live_since_check);
			++(vm->player[i]->live_total);
			(vm->player[i]->live_last) = vm->cycle_total;
			++vm->live_since_check;
			return (SUCCESS);
		}
		++i;
	}
	return (FAILURE);
}
