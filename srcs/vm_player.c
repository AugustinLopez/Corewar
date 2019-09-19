/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:53:07 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/19 11:37:16 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

void	print_all_players(t_vm *vm)
{
	uint8_t	i;

	i = 0;
	while (i < vm->player_total)
	{
		ft_printf("%s%sPlayer %u:%s\n",
			FT_UNDER, FT_BOLD, i + 1, FT_EOC);
		ft_printf("\t%sID:%s\t\t %d\n",
			FT_UNDER, FT_EOC, (vm->player[i]).id);
		ft_printf("\t%sName:%s\t\t %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).name);
		ft_printf("\t%sComment:%s\t %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).comment);
		ft_printf("\t%sLive now:%s\t %zu\n",
			FT_UNDER, FT_EOC, (vm->player[i]).live_since_check);
		ft_printf("\t%sLive total:%s\t %zu\n",
			FT_UNDER, FT_EOC, (vm->player[i]).live_total);
		ft_printf("\t%sAlive ?%s\t\t %s\n",
			FT_UNDER, FT_EOC, (vm->player[i]).still_alive ? "Yes" : "No");
		++i;
		ft_putchar('\n');
	}
}

int		init_player(t_vm *vm, int index, char *name, char *comment)
{
	uint8_t	i;

	i = 0;
	while (i < vm->player_total)
		if ((vm->player[i++]).id == index)
			return (FAILURE);
	++(vm->player_total);
	(vm->player[i]).id = index;
	(vm->player[i]).name = name;
	(vm->player[i]).comment = comment;
	(vm->player[i]).still_alive = TRUE;
	return (SUCCESS);
}

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
