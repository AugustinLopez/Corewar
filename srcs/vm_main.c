/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/11 18:03:42 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
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

int		set_no_n_option(t_argument *arg)
{
	int	i;
	int	k;

	k = -1;
	i = arg->nbr_player + 1;
	while (--i > 0)
		if (arg->n_option[i - 1] == 0)
			arg->value[i - 1] = k--;
	return (k);
}

int	check_duplicate_id(t_argument *arg)
{
	int	i;
	int	j;
	int	id;

	id = set_no_n_option(arg);
	i = arg->nbr_player;
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
	return (FALSE);
}

int	get_argument_data(t_argument *arg, int argc, char **argv)
{
	ft_bzero(arg, sizeof(*arg));
	arg->ac = argc;
	arg->av = argv;
	arg->dump_option = FALSE;
	ft_memset(&(arg->n_option), FALSE, sizeof(arg->n_option));
	if (parser(arg) == SUCCESS && check_duplicate_id(arg) == FALSE)
		return (SUCCESS);
	if (!ft_strcmp(arg->av[arg->i], "-n"))
	{
		ft_dprintf(STDERR_FILENO, "Error at %d: '-n", arg->i);
		if (arg->i + 1 < argc)
			ft_dprintf(STDERR_FILENO, " %s", arg->av[arg->i + 1]);
		if (arg->i + 2 < argc)
			ft_dprintf(STDERR_FILENO, " %s", arg->av[arg->i + 2]);
		ft_dprintf(STDERR_FILENO, "'\n");
	}
	else if (!ft_strcmp(arg->av[arg->i], "-dump"))
	{
		ft_dprintf(STDERR_FILENO, "Error at %d: '-dump", arg->i);
		if (arg->i + 1 < argc)
			ft_dprintf(STDERR_FILENO, " %s", arg->av[arg->i + 1]);
		ft_dprintf(STDERR_FILENO, "'\n");
	}
	else
		ft_dprintf(STDERR_FILENO, "Error at %d: '%s'\n", arg->i, arg->av[arg->i]);
	return (FAILURE);
}

int	main(int argc, char **argv)
{
	int			i;
	t_argument	arg;

	if (argc == 1)
		return (print_usage());
	if (get_argument_data(&arg, argc, argv) == FAILURE)
		return (-1);
	ft_printf("cycle_to_dump : |%zu|\n", arg.dump_value);
	i = 0;
	while (i < arg.nbr_player)
	{
		ft_printf("option   : |%d|\n", arg.n_option[i]);
		ft_printf("valeur n : |%d|\n", arg.value[i]);
		ft_printf("fichier  : |%s|\n\n", arg.file[i]);
		i += 1;
	}
	return (0);
}
