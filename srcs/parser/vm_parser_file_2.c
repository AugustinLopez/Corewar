/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_file_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:43:54 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/16 11:50:00 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		vm_set_error(t_vm *vm, int err, char *strerr)
{
	vm->err = err;
	vm->strerr = strerr;
	return (FAILURE);
}

/*
** Because we don't forbid any player to set -n 0, or any value,
** we need to choose a value that's different from all players. Otherwise
** the color will be unreliable.
*/

void	vm_set_null_id(t_vm *vm, t_argument *arg)
{
	int		val;
	size_t	j;

	j = 0;
	while (j < MAX_PLAYERS)
	{
		vm->player[j].id = arg->value[j];
		j++;
	}
	j = 0;
	val = 0;
	while (j < MAX_PLAYERS)
	{
		if (val == vm->player[j++].id)
		{
			val++;
			j = 0;
		}
	}
	j = 0;
	while (j < MEM_SIZE)
		vm->ram[j++].player_last = val;
}
