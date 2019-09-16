/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/16 11:33:00 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_vm		vm;

	if (parser(&vm, argc, argv) == FAILURE)
		return (-1);
	dump_memory(&vm, 64);
	access_all_players(&vm);
	access_all_processes(&vm);
	free_all_players(&vm);
	free_all_processes(&vm);
	return (0);
}
