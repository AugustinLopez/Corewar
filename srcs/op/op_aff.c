/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:50:49 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 12:12:58 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_aff(t_vm *vm, t_process *proc)
{
	if (0 < proc->op.p[0] && proc->op.p[0] <= REG_NUMBER)
		return (FAILURE);
	ft_print("Aff : |%c|\n", proc->r[proc->op.p[0] - 1] % 256);
	proc->carry = (proc->r[proc->op.p[0] - 1] % 256 == 0) ? 1 : 0;
	return (SUCCESS);
}
