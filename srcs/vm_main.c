/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/26 12:40:18 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

int	corewar(t_vm *vm)
{
	size_t	cycle;

	introduce_player(vm);
	if (vm->cycle_to_dump == 0)
	{
		while (proceed_cycle(vm) == 1)
			continue ;
		ft_printf("%zu\n", vm->cycle_total);
	}
	else
	{
		cycle = 0;
		while (cycle++ <= vm->cycle_to_dump)
			if (proceed_cycle(vm) == 0)
				break ;
	}
	if (vm->cycle_to_dump == 0)
	{
		print_winner(vm);
		return (SUCCESS);
	}
	dump_memory(vm, 64, FALSE);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_vm		vm;
	char		*buff;
	int			i;
	int			j;
	t_bool		over;
	t_process	*proc;

	(void)i;
	(void)buff;
	if (parser(&vm, argc, argv) == FAILURE)
		return (-1);
	(void)proc;
	//corewar(&vm);
	introduce_player(&vm);
	i = 0;
	proc = vm.process;
	/*while (proc)
	{
		(void)analyze_process(&vm, proc);
		proc = proc->next;
	}*/
	over = FALSE;
	dump_memory(&vm, 64, TRUE);
	j = 1;
	while (ft_gnl(1, &buff, 0) > 0)
	{
		if (*buff)
		{
			j = ft_atoi(buff);
			if (j <= 0)
				j = 1;
		}
		i = 0;
		while (i++ < j)
		{
			if (proceed_cycle(&vm) == 0)
			{
				over = TRUE;
				break ;
			}
		}
		ft_printf("%sCycle %zu%s:\n", FT_UNDER, vm.cycle_total, FT_EOC);
		dump_memory(&vm, 64, TRUE);
		free(buff);
		buff = 0;
		if (over == TRUE)
			break ;
	}
	free(buff);
	buff = 0;
	print_winner(&vm);
	dump_memory(&vm, 64, TRUE);
	//print_all_players(&vm);*/
	//print_all_processes(&vm);
	free_all_players(&vm);
	free_all_processes(&vm);
	return (0);
}
