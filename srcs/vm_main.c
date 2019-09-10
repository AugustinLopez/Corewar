/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/10 17:27:40 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct 		s_vm
{
	size_t			cycle_to_dump;
	int				player[4];
}					t_vm;

int check_argc(int argc)
{
	if (argc == 1)
	{
		ft_printf("%susage%s: %s./corewar%s [%s-dump nbr_cycles%s] ",
				FT_UNDER, FT_EOC, FT_BOLD, FT_EOC, FT_BOLD, FT_EOC);
		ft_printf("[[%s-n number%s] %schampion1.cor%s] ...\n",
				FT_BOLD, FT_EOC, FT_BOLD, FT_EOC);
		return (-1);
	}
	return (0);
}

int ft_isnb_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit((int)str[i]))
			return (-1);
		i += 1;;
	}
	return (0);
}

/*
** Parse for cycle_to_dump value :
** Check if argv[i + 1] exist and if it is a positive number.
** Store into vm->cycle_to_dump if yes, else return -1.
*/

int parse_dump(int argc, char **argv, t_vm *vm, size_t *i)
{
	if ((*i + 1 < argc) && (ft_isnb_str(argv[*i + 1]) == 0))
		vm->cycle_to_dump = ft_atozu(argv[++*i]);
	else
		return (-1);
	return (0);
}

int	parse_n(int ac, char **av, t_vm *vm, size_t *i)
{
	char	*s;

	if ((*i + 1 < ac) && (*i + 2 < ac) && ft_isnb_str(av[*i + 1]) == 0
			&& (s = ft_strstr(av[*i + 2], ".cor")) && s != av[*i + 2] && !s[4])
	{
		// plus de check a faire sur le player (duplicate, si trop de player...)
		// 4 lignes qui suivent doivent etre remplacees
		if (!vm->player[0])
			vm->player[0] = ft_atozu(av[*i + 1]);
		else if (!vm->player[1])
			vm->player[1] = ft_atozu(av[*i + 1]);
		*i += 2;
	}
	else
	{
		//ft_printf("NOPE\n"); //debug
		return (-1);
	}
	return (0);
}

int	parse_options(int ac, char **av, t_vm *vm)
{
	size_t	i;
	char	*s;
	
	i = 1;
	if (check_argc(ac) == -1)
		return (-1);
	while (i < ac && av[i])
	{
		if (!ft_strcmp(av[i], "-dump") && parse_dump(ac, av, vm, &i) == -1)
			return (-1);
		else if (!ft_strcmp(av[i], "-n") && parse_n(ac, av, vm, &i) == -1)
			return (-1);
		else if ((s = ft_strstr(av[i], ".cor")) && s != av[i] && !s[4])
			;	
			//parse_player(ac, av, &vm, &i); // TODO
		else
			;
		i += 1;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int i;
	t_vm vm;

	//verif valeurs du op.h n'ont pas ete modifies !
	ft_bzero(&vm, sizeof(vm));
	if (parse_options(argc, argv, &vm) == 0)
	{
		ft_printf("cycle_to_dump : |%zu|\n", vm.cycle_to_dump);
		ft_printf("player_1_nb : |%zu|\n", vm.player[0]);
		ft_printf("player_2_nb : |%zu|\n", vm.player[1]);
	}
	return (0);
}
