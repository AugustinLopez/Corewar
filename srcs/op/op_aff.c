/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:50:49 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/27 16:52:12 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_aff(t_vm *vm, t_process *proc)
{
	int	ret;

	ret = SUCCESS;
	if (load_from_ocp(vm, proc, 1, 0) == FAILURE)
		ret = FAILURE;
	if (!((proc->op.ocp & 0xf0) == 0x40))
	{
		//proc->next_pc = (proc->next_pc + 1) % MEM_SIZE;
		ret = FAILURE;
	}
	if (ret == FAILURE)
		return (ret);
	if (vm->flag & FLAG_VISU)
		ft_printf("Aff: %c\n", proc->r[(proc->op.p[0]) - 1] % 256);
	return (SUCCESS);
}
