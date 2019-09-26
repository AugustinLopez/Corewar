/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/26 14:38:12 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"

static inline int	parse_cor(t_argument *arg, char *s, int *i)
{
	if (s[EXT_LENGTH])
		return (arg_set_error(arg, ERR_NOT_A_COR, *i));
	else if (arg->nbr_player >= MAX_PLAYERS)
		return (arg_set_error(arg, ERR_TOO_MANY, *i));
	arg->file[arg->nbr_player] = arg->av[*i];
	arg->nbr_player += 1;
	return (SUCCESS);
}

/*
** 18446744073709551615
** 9223372036854775807
*/

static inline int	parse_dump(t_argument *arg, int *i)
{
	if (arg->dump_option == TRUE)
		return (arg_set_error(arg, ERR_TWO_DUMP, *i));
	if (!((*i + 1) < arg->ac))
		return (arg_set_error(arg, ERR_MISS_AV, *i + 1));
	if (arg->av[*i + 1][0] == '-')
		return (arg_set_error(arg, ERR_NEGATIVE, *i + 1));
	arg->dump_value = arg_atozu(arg, arg->av[++*i]);
	if (arg->err)
		return (FAILURE);
	arg->dump_option = TRUE;
	return (SUCCESS);
}

/*
** 2147483647
*/

static inline int	parse_n(t_argument *arg, int *i)
{
	char	*s;

	if (!(*i + 1 < arg->ac))
		return (arg_set_error(arg, ERR_MISS_AV, *i + 1));
	else if (!(*i + 2 < arg->ac))
		return (arg_set_error(arg, ERR_MISS_AV, *i + 2));
	else if (!(s = ft_strrstr(arg->av[*i + 2], FILE_EXT)) || s[EXT_LENGTH])
		return (arg_set_error(arg, ERR_NOT_A_COR, *i + 2));
	else if (arg->nbr_player >= MAX_PLAYERS)
		return (arg_set_error(arg, ERR_TOO_MANY, *i));
	arg->value[arg->nbr_player] = arg_atoi(arg, arg->av[++*i]);
	if (arg->err)
		return (FAILURE);
	arg->n_option[arg->nbr_player] = TRUE;
	arg->file[arg->nbr_player] = arg->av[++*i];
	arg->nbr_player += 1;
	return (SUCCESS);
}

static inline int	argv_parser_iterate(t_argument *arg)
{
	char	*s;
	int		ret;

	arg->i = 0;
	while (++(arg->i) < arg->ac)
	{
		if (!ft_strcmp(arg->av[(arg->i)], "-dump")
				|| !ft_strcmp(arg->av[(arg->i)], "-d"))
			ret = parse_dump(arg, &(arg->i));
		else if (!ft_strcmp(arg->av[(arg->i)], "-n"))
			ret = parse_n(arg, &(arg->i));
		else if (!ft_strcmp(arg->av[(arg->i)], "-v"))
			arg->flag |= FLAG_VISU;
		else if (!ft_strcmp(arg->av[(arg->i)], "-m"))
			arg->flag |= FLAG_MORE_INFO;
		else if (!ft_strcmp(arg->av[(arg->i)], "-l"))
			arg->flag |= FLAG_LESS_INFO;
		else if ((s = ft_strrstr(arg->av[(arg->i)], FILE_EXT)))
			ret = parse_cor(arg, s, &(arg->i));
		else
			ret = arg_set_error(arg, ERR_INVALID, arg->i);
		if (ret == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int					argv_parser(t_argument *arg, int argc, char **argv)
{
	ft_bzero(arg, sizeof(*arg));
	arg->ac = argc;
	arg->av = argv;
	arg->dump_option = FALSE;
	ft_memset(&(arg->n_option), FALSE, sizeof(arg->n_option));
	if (argv_parser_iterate(arg) == SUCCESS
			&& handle_duplicate_id(arg) == FALSE
			&& arg->nbr_player >= 2)
		return (SUCCESS);
	return (FAILURE);
}
