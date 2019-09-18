/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_XXX_proceed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 09:41:09 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/18 13:46:50 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int	op_zjmp_proceed(t_vm *vm, t_process *proc)
{
	size_t	jump_size;

	jump_size = ((size_t)load_from_ram(vm, proc, 2)) % IDX_MOD;
	proc->pc = proc->carry == 1 ? (proc->pc + jump_size) % MEM_SIZE : (proc->pc
			+ 3) % MEM_SIZE;
	return (SUCCESS);
}
