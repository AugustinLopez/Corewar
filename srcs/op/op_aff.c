/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:50:49 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/30 11:06:10 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_aff(t_vm *vm, t_process *proc)
{
	if (load_from_ocp(vm, proc, 1, 0) == FAILURE
			|| !((proc->op.ocp & 0xf0) == 0x40))
		return (FAILURE);
	if (vm->flag & FLAG_VISU)
		ft_printf("Aff: %c\n", proc->r[(proc->op.p[0]) - 1] % 256);
	return (SUCCESS);
}
