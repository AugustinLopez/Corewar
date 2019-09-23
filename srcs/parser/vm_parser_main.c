/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:28:10 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/23 15:45:44 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <unistd.h>
#include <errno.h>

static inline void	print_usage(void)
{
	ft_printf("%susage%s: ./corewar [%s-dump%s %snbr_cycles%s] ",
			FT_UNDER, FT_EOC, FT_BOLD, FT_EOC, FT_UNDER, FT_EOC);
	ft_printf("[[%s-n%s %snumber%s] champion1.cor] ...\n",
			FT_BOLD, FT_EOC, FT_UNDER, FT_EOC);
}

static inline void	arg_error_message(t_argument *arg)
{
	if (!arg->err && arg->nbr_player < 2)
	{
		ft_dprintf(STDERR_FILENO, "Error: Not enough players.\n");
		return ;
	}
	ft_dprintf(STDERR_FILENO, "Error: Argument %d '%s':\n", arg->i,
		arg->i < arg->ac ? arg->av[arg->i] : "");
	if (arg->err == ERR_NOT_A_COR)
		ft_dprintf(STDERR_FILENO, "Expected a .cor file.\n");
	else if (arg->err == ERR_TWO_DUMP)
		ft_dprintf(STDERR_FILENO, "Cannot have more than one -dump.\n");
	else if (arg->err == ERR_NEGATIVE)
		ft_dprintf(STDERR_FILENO, "Expected a positive value.\n");
	else if (arg->err == ERR_TOO_BIG)
		ft_dprintf(STDERR_FILENO, "Number out of range.\n");
	else if (arg->err == ERR_NOT_A_NUM)
		ft_dprintf(STDERR_FILENO, "Expected a number.\n");
	else if (arg->err == ERR_MISS_AV)
		ft_dprintf(STDERR_FILENO, "Missing argument.\n");
	else if (arg->err == ERR_TOO_MANY)
		ft_dprintf(STDERR_FILENO, "Too many players.\n");
	else if (arg->err == ERR_INVALID)
		ft_dprintf(STDERR_FILENO, "Invalid argument.\n");
	else if (arg->err == ERR_DUPLICATE)
		ft_dprintf(STDERR_FILENO, "Players cannot share the same ID.\n");
}

static inline void	vm_error_message(t_vm *vm)
{
	ft_dprintf(STDERR_FILENO, "Error: file '%s':\n", vm->strerr);
	if (vm->err == ERR_OPEN)
		ft_dprintf(STDERR_FILENO, "Could not open file.\n");
	else if (vm->err == ERR_CLOSE)
		ft_dprintf(STDERR_FILENO, "Could not close file.\n");
	else if (vm->err == ERR_NAME || vm->err == ERR_COMMENT
			|| vm->err == ERR_CODE || vm->err == ERR_WEIGHT)
		ft_dprintf(STDERR_FILENO, "File is either unreadable or too short\n");
	else if (vm->err == ERR_MAGIC)
		ft_dprintf(STDERR_FILENO, ".cor identifier missing\n");
	else if (vm->err == ERR_MAX_SIZE)
		ft_dprintf(STDERR_FILENO, "Code is too large\n");
	else if (vm->err == ERR_MEMORY)
		ft_dprintf(STDERR_FILENO, "Not enough memory\n");
	else if (vm->err == ERR_HEADER)
		ft_dprintf(STDERR_FILENO, "Program and header weights don't match\n");
	ft_dprintf(STDERR_FILENO, "%d\n",  vm->err);
}

int					parser(t_vm *vm, int argc, char **argv)
{
	t_argument	arg;

	vm->err = 0;
	if (argc == 1)
		print_usage();
	else if (argv_parser(&arg, argc, argv) == FAILURE)
	{
		vm->err = errno;
		arg_error_message(&arg);
	}
	else if (file_parser(vm, &arg) == FAILURE)
	{
		arg.err = errno;
		vm_error_message(vm);
		vm->err = arg.err;
		free_all_players(vm);
		free_all_processes(vm);
	}
	else
		return (SUCCESS);
	if (vm->err)
		ft_dprintf(STDERR_FILENO, "\n(Errno: %d)\n", vm->err);
	return (FAILURE);
}
