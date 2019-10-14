/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 14:06:29 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/16 14:35:22 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	analyze_process(t_vm *vm, t_process *proc)
{
	if (proc->cycle_to_wait)
	{
		--(proc->cycle_to_wait);
		return (SUCCESS);
	}
	if (proc->op->op == 0)
		return (load_new_process(vm, proc));
	if (proc->op-op == 1)
		return (op_life(vm, proc));
	if (proc->op->op == 2)
		return (op_ld(vm, proc));
	else
		return (load_new_process(vm, proc));
}
