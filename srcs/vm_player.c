/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/30 13:14:45 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

void	free_all_players(t_vm *vm)
{
	uint8_t	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if ((vm->player[i]).name)
			free((vm->player[i]).name);
		if ((vm->player[i]).comment)
			free((vm->player[i]).comment);
		++i;
	}
}
