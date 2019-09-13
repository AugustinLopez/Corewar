/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/12 17:47:05 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "corewar.h"
#include "libft.h"

int	print_usage(void)
{
	ft_printf("%susage%s: ./corewar [%s-dump%s %snbr_cycles%s] ",
			FT_UNDER, FT_EOC, FT_BOLD, FT_EOC, FT_UNDER, FT_EOC);
	ft_printf("[[%s-n%s %snumber%s] champion1.cor] ...\n",
			FT_BOLD, FT_EOC, FT_UNDER, FT_EOC);
	return (-1);
}

void	arg_error_message(t_argument *arg)
{
	if (!arg->err && arg->nbr_player < 2)
	{
		ft_dprintf(STDERR_FILENO, "Error: Not enough players.\n");
		return ;
	}
	ft_dprintf(STDERR_FILENO,"Error: Argument %d '%s':\n", arg->i,
		arg->i < arg->ac ? arg->av[arg->i] : "");
	if (arg->err == ERR_NOT_A_COR)
		ft_dprintf(STDERR_FILENO,"Expected a .cor file.\n");
	else if (arg->err == ERR_TWO_DUMP)
		ft_dprintf(STDERR_FILENO,"Cannot have more than one -dump.\n");
	else if (arg->err == ERR_NEGATIVE)
		ft_dprintf(STDERR_FILENO,"Expected a positive value.\n");
	else if (arg->err == ERR_TOO_BIG)
		ft_dprintf(STDERR_FILENO,"Number out of range.\n");
	else if (arg->err == ERR_NOT_A_NUM)
		ft_dprintf(STDERR_FILENO,"Expected a number.\n");
	else if (arg->err == ERR_MISS_AV)
		ft_dprintf(STDERR_FILENO,"Missing argument.\n");
	else if (arg->err == ERR_TOO_MANY)
		ft_dprintf(STDERR_FILENO,"Too many players.\n");
	else if (arg->err == ERR_INVALID)
		ft_dprintf(STDERR_FILENO,"Invalid argument.\n");
	else if (arg->err == ERR_DUPLICATE)
		ft_dprintf(STDERR_FILENO,"Players cannot share the same ID.\n");
}

void	vm_error_message(t_vm *vm)
{
	ft_dprintf(STDERR_FILENO, "Error: file '%s':\n", vm->strerr);
	if (vm->err == ERR_OPEN)
		ft_dprintf(STDERR_FILENO, "Could not open file.\n");
	else if (vm->err == ERR_CLOSE)
		ft_dprintf(STDERR_FILENO, "Could not close file.\n");
	else if (vm->err == ERR_NAME || vm->err == ERR_COMMENT
			|| vm->err == ERR_CODE)
		ft_dprintf(STDERR_FILENO, "File is either unreadable or too short\n");
	else if (vm->err == ERR_MAGIC)
		ft_dprintf(STDERR_FILENO, ".cor identifier missing\n");
	else if (vm->err == ERR_MAX_SIZE)
		ft_dprintf(STDERR_FILENO, "Code is too large\n");
	else if (vm->err == ERR_MEMORY)
		ft_dprintf(STDERR_FILENO, "Not enought memory\n");
}

int		set_no_n_option(t_argument *arg)
{
	int	i;
	int	j;

	j = -1;
	i = arg->nbr_player + 1;
	while (--i > 0)
		if (arg->n_option[i - 1] == 0)
			arg->value[i - 1] = j--;
	return (j);
}

int	check_duplicate_id(t_argument *arg)
{
	int	i;
	int	j;
	int	id;

	id = set_no_n_option(arg);
	i = arg->nbr_player;
	arg->err = ERR_DUPLICATE;
	while (--i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (arg->value[i] == arg->value[j])
			{
				if (arg->n_option[j] == 1 && arg->n_option[i] == 1)
					return (TRUE);
				arg->value[arg->n_option[j] == 0 ? j : i] = id--;
				i = arg->nbr_player;
				break ;
			}
			j += 1;
		}
	}
	arg->err = 0;
	return (FALSE);
}

int	get_argument_data(t_argument *arg, int argc, char **argv)
{
	ft_bzero(arg, sizeof(*arg));
	arg->ac = argc;
	arg->av = argv;
	arg->dump_option = FALSE;
	ft_memset(&(arg->n_option), FALSE, sizeof(arg->n_option));
	if (argument_parser(arg) == SUCCESS
			&& check_duplicate_id(arg) == FALSE
			&& arg->nbr_player >= 2)
		return (SUCCESS);
	arg_error_message(arg);
	return (FAILURE);
}

void	vm_set_player_id(t_vm *vm, t_argument *arg)
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

int	put_data_in_vm(t_vm *vm, t_argument *arg)
{
	size_t	pc;

	ft_bzero(vm, sizeof(*vm));
	vm_set_player_id(vm, arg);
	while (vm->player_total < arg->nbr_player)
	{
		vm->player[vm->player_total].id = arg->value[vm->player_total];
		if (read_cor(arg, vm) == FAILURE)
		{
			vm_error_message(vm);
			return (FAILURE);
		}
		pc = vm->player_total * MEM_SIZE / arg->nbr_player;
		if (create_process(vm, pc, vm->player[vm->player_total].id) == FAILURE)
		{
			vm->err = ERR_MEMORY;
			vm->strerr = arg->file[vm->player_total];
			vm_error_message(vm);
			return (FAILURE);
		}
		vm->process->pc = pc;
		vm->process->r[0] = (vm->player[vm->player_total]).id;
		vm->player_total += 1;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_argument	arg;
	t_vm		vm;

	if (argc == 1)
		return (print_usage());
	if (get_argument_data(&arg, argc, argv) == FAILURE)
		return (-1);
	if (put_data_in_vm(&vm, &arg) == FAILURE)
	{
		free_all_players(&vm);
		free_all_processes(&vm);
		return (-1);
	}
	/*ft_printf("cycle_to_dump : |%zu|\n", arg.dump_value);
	i = 0;
	while (i < arg.nbr_player)
	{
		ft_printf("option   : |%d|\n", arg.n_option[i]);
		ft_printf("valeur n : |%d|\n", arg.value[i]);
		ft_printf("fichier  : |%s|\n\n", arg.file[i]);
		i += 1;
	}*/
	dump_memory(&vm, 64);
	access_all_players(&vm);
	access_all_processes(&vm);
	free_all_players(&vm);
	free_all_processes(&vm);
	return (0);
}
