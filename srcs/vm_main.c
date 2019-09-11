/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/11 15:39:19 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

#define MAX_PLAYERS 4
#define FAILURE 0
#define SUCCESS 1
#define FALSE 0
#define TRUE 1

typedef struct		s_player_ac
{
	int				n_option[MAX_PLAYERS];
	int				value[MAX_PLAYERS];
	char			*file_av[MAX_PLAYERS];
	int				dump_option;
	size_t			dump_value;
	int				i;
}					t_player_ac;

typedef struct 		s_vm
{
	size_t			cycle_to_dump;
	size_t			player[MAX_PLAYERS];
	size_t			player_total;
}					t_vm;

int	check_argc(int ac)
{
	if (ac == 1)
	{
		ft_printf("%susage%s: %s./corewar%s [%s-dump nbr_cycles%s] ",
				FT_UNDER, FT_EOC, FT_BOLD, FT_EOC, FT_BOLD, FT_EOC);
		ft_printf("[[%s-n number%s] %schampion1.cor%s] ...\n",
				FT_BOLD, FT_EOC, FT_BOLD, FT_EOC);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_isnb_str(char *str)
{
	int i;
	int	j;

	i = 0;
	if (str[0] == '-')
		i += 1;
	j = i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FAILURE);
		i += 1;
	}
	if (i == j)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_dump(int ac, char **av, t_player_ac *pac, size_t *i)
{
	if (pac->dump_option == 1)
		return (FAILURE);
	pac->dump_option = 1;
	if ((*i + 1 < ac) && (ft_isnb_str(av[*i + 1]) == SUCCESS))
	{
		if (av[*i + 1][0] == '-')
			return (FAILURE);
		pac->dump_value = ft_atozu(av[++*i]); // check atozu parse
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	insert_player_n(int ac, char **av, t_player_ac *pac, size_t *i)
{
	if (pac->i >= MAX_PLAYERS)
		return (FAILURE);
	pac->n_option[pac->i] = 1;
	pac->value[pac->i] = ft_atoi(av[*i + 1]); //update ft_atoi for error checking
	pac->file_av[pac->i] = av[*i + 2];
	pac->i += 1;
	return (SUCCESS);
}

int	parse_n(int ac, char **av, t_player_ac *pac, size_t *i)
{
	char	*s;

	if ((*i + 1 < ac) && (*i + 2 < ac) && ft_isnb_str(av[*i + 1]) == SUCCESS
			&& (s = ft_strrstr(av[*i + 2], ".cor")) && !s[4])
	{
		if (insert_player_n(ac, av, pac, i) == FAILURE)
			return (FAILURE);
		*i += 2;
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	insert_player(int ac, char **av, t_player_ac *pac, size_t *i)
{
	if (pac->i >= MAX_PLAYERS)
		return (FAILURE);
	pac->file_av[pac->i] = av[*i];
	pac->i += 1;
	return (SUCCESS);
}

int	parse_options(int ac, char **av, t_player_ac *pac)
{
	size_t	i;
	char	*s;
	
	i = 1;
	if (check_argc(ac) == FAILURE)
		return (FAILURE);
	while (i < ac)
	{
		// room for options -[a-z]
		if (!ft_strcmp(av[i], "-dump"))
		{
			if (parse_dump(ac, av, pac, &i) == FAILURE)
				return (FAILURE);
		}
		else if (!ft_strcmp(av[i], "-n"))
		{
			if (parse_n(ac, av, pac, &i) == FAILURE)
				return (FAILURE);
		}
		else if ((s = ft_strrstr(av[i], ".cor")))
		{
			if (s[4] || insert_player(ac, av, pac, &i) == FAILURE)
				return (FAILURE);
		}
		else
			return (FAILURE);
		i += 1;
	}
	return (SUCCESS);
}

void	remove_non_set_zero(t_player_ac *pac, int *k)
{
	int	i;

	i = pac->i;
	while (--i > 0)
		if (pac->n_option[i] == 0)
			pac->value[i] = (*k)--;
}

int	check_duplicate_id(t_player_ac *pac)
{
	int	i;
	int	j;
	int	k;

	k = -1;
	remove_non_set_zero(pac, &k);
	i = pac->i;
	while (--i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (pac->value[i] == pac->value[j])
			{
				if ( pac->n_option[j] == 1 && pac->n_option[i] == 1)
					return (TRUE);
				pac->value[pac->n_option[j] == 0 ? j : i] = k--;
				i = pac->i;
				break ;
			}
			j += 1;
		}
	}
	return (FALSE);
}

int	main(int argc, char **argv)
{
	int			i;
	t_vm		vm;
	t_player_ac	pac;

	ft_bzero(&vm, sizeof(vm));
	ft_bzero(&pac, sizeof(pac));
	if (parse_options(argc, argv, &pac) == SUCCESS)
	{
		if (check_duplicate_id(&pac) == FALSE)
		{
			ft_printf("cycle_to_dump : |%zu|\n", pac.dump_value);
			i = 0;
			while (i < 4)
			{
				ft_printf("option   : |%d|\n", pac.n_option[i]);
				ft_printf("valeur n : |%d|\n", pac.value[i]);
				ft_printf("fichier  : |%s|\n\n", pac.file_av[i]);
				i += 1;
			}
		}
	}
	return (0);
}
