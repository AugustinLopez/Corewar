/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:50:49 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/20 11:59:53 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int	op_aff(t_process *proc)
{
	if (!(0 < (proc->op.p[0] >> 8) && (proc->op.p[0] >> 8) <= REG_NUMBER))
		return (FAILURE);
	if (!((proc->op.ocp & 0xf0) == 0x40))
		return (FAILURE);
	ft_printf("Aff : %c\n", proc->r[(proc->op.p[0] >> 8) - 1] % 256);
	return (SUCCESS);
}
