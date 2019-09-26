/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/26 16:20:15 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <stdlib.h>

int	standard_corewar_dump(t_vm *vm)
{
	size_t	cycle;
	int		ret;

	ret = 0;
	cycle = 0;
	while (cycle++ <= vm->cycle_to_dump)
		if ((ret = gameloop(vm)) == 0)
			break ;
	dump_memory(vm, 64, FALSE);
	if (ret == 0)
	{
		ft_printf("%s%sTotal number of cycle%s: %zu\n"
				, FT_BOLD, FT_UNDER, FT_EOC, vm->cycle_total);
		print_winner(vm);
	}
	return (SUCCESS);
}

int	standard_corewar(t_vm *vm)
{
	while (gameloop(vm) == 1)
		continue ;
	if (vm->flag & FLAG_MORE_INFO)
		ft_printf("%s%sTotal number of cycle%s: %zu\n"
				, FT_BOLD, FT_UNDER, FT_EOC, vm->cycle_total);
	print_winner(vm);
	return (SUCCESS);
}

int	corewar_loop(t_vm *vm, int *loop)
{
	char	*buff;
	int		i;
	int		ret;

	ft_printf("\n%sCommand input >%s ", FT_ITALIC, FT_EOC);
	if (ft_gnl(1, &buff, 0) <= 0)
		return (-1);
	if (*buff)
	{
		if (!ft_strcmp(buff, "over"))
		{
			free(buff);
			return (-1);
		}
		*loop = ft_atoi(buff);
		*loop = *loop <= 0 ? 1 : *loop;
	}
	free(buff);
	i = 0;
	while (i++ < *loop)
		if ((ret = gameloop(vm)) == 0)
			break ;
	ft_printf("%sCycle %zu%s:\n", FT_UNDER, vm->cycle_total - 1, FT_EOC);
	dump_memory(vm, 64, TRUE);
	return (ret);
}

int	visual_corewar(t_vm *vm)
{
	int		j;
	int		ret;

	j = 1;
	dump_memory(vm, 64, TRUE);
	while ((ret = corewar_loop(vm, &j)) == 1)
		continue ;
	if (ret == 0)
		print_winner(vm);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_vm vm;

	if (parser(&vm, argc, argv) == FAILURE)
		return (-1);
	introduce_player(&vm);
	if (vm.flag & FLAG_VISU)
		visual_corewar(&vm);
	else if (vm.cycle_to_dump != 0)
		standard_corewar_dump(&vm);
	else if (vm.cycle_to_dump == 0)
		standard_corewar(&vm);
	ft_gnl(-1, 0, -1);
	free_all_players(&vm);
	free_all_processes(&vm);
	return (0);
}
