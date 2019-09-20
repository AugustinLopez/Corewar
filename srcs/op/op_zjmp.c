/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:41:09 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/20 14:59:53 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdint.h>

int	op_zjmp(t_process *proc)
{
	int16_t	addr;

	addr = (proc->carry == 1) ? proc->op.p[0] % IDX_MOD : 3;
	proc->next_pc = (proc->pc + addr) % MEM_SIZE;
	if (proc->next_pc < 0)
		proc->next_pc = MEM_SIZE - proc->next_pc;
	return (SUCCESS);
}
