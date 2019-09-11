/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/11 18:03:25 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "corewar.h"
#include "libft.h"

int	is_valid_number(char *str)
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
			return (FALSE);
		i += 1;
		if (i > LOG_UINT64_MAX + 1)
			return (FALSE);
	}
	if (i == j)
		return (FALSE);
	return (TRUE);
}

int	parse_cor(t_argument *arg, char *s, int *i)
{
	if (s[4] || arg->nbr_player >= MAX_PLAYERS)
		return (FAILURE);
	arg->file[arg->nbr_player] = arg->av[*i];
	arg->nbr_player += 1;
	return (SUCCESS);
}

int	parse_dump(t_argument *arg, int *i)
{
	if (arg->dump_option == TRUE)
		return (FAILURE);
	arg->dump_option = TRUE;
	if ((*i + 1 < arg->ac) && (is_valid_number(arg->av[*i + 1]) == TRUE))
	{
		if (arg->av[*i + 1][0] == '-')
			return (FAILURE);
		arg->dump_value = ft_atozu(arg->av[++*i]); // check atozu parse
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	parse_n(t_argument *arg, int *i)
{
	char	*s;

	if ((*i + 2 < arg->ac)
			&& is_valid_number(arg->av[*i + 1]) == TRUE
			&& (s = ft_strrstr(arg->av[*i + 2], ".cor"))
			&& !s[4]
			&& arg->nbr_player < MAX_PLAYERS)
	{
		arg->n_option[arg->nbr_player] = TRUE;
		arg->value[arg->nbr_player] = ft_atoi(arg->av[*i + 1]); //update ft_atoi for error checking
		arg->file[arg->nbr_player] = arg->av[*i + 2];
		arg->nbr_player += 1;
		*i += 2;
		return (SUCCESS);
	}
	return (FAILURE);
}

int	parser(t_argument *arg)
{
	char	*s;
	int		ret;
	
	arg->i = 0;
	ret = SUCCESS;
	while (++(arg->i) < arg->ac)
	{
		if (!ft_strcmp(arg->av[(arg->i)], "-dump"))
			ret = parse_dump(arg, &(arg->i));
		else if (!ft_strcmp(arg->av[(arg->i)], "-n"))
			ret = parse_n(arg, &(arg->i));
		else if ((s = ft_strrstr(arg->av[(arg->i)], ".cor")))
			ret = parse_cor(arg, s, &(arg->i));
		else
			ret = FAILURE;
		if (ret == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
