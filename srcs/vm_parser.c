/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/12 17:04:09 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "corewar.h"
#include "libft.h"

size_t	arg_atozu(t_argument *arg, const char *src)
{
	size_t	ui;

	if (*src == '+')
		++src;
	if (!*src)
		arg->err = ERR_NOT_A_NUM;
	ui = 0;
	while ('0' <= *src && *src <= '9' && ui < POW10_LOG_SIZE_MAX / 10)
		ui = ui * 10 + *(src++) - '0';
	if ('0' <= *src && *src <= '9')
	{
		if (ui > SIZE_MAX / 10
			|| (ui == SIZE_MAX / 10 && (size_t)(*src - '0') > SIZE_MAX % 10))
		{
			arg->err = ERR_TOO_BIG;
			return (-1);
		}
		ui = ui * 10 + *src++ - '0';
	}
	if ('0' <= *src && *src <= '9')
		arg->err = ERR_TOO_BIG;
	else if (*src)
		arg->err = ERR_NOT_A_NUM;
	return (ui);
}

int	arg_atoi(t_argument *arg, const char *src)
{
	uint8_t			minus;
	unsigned long	ui;

	ui = 0;
	minus = (*src == '-') ? 1 : 0;
	if (*src == '-' || *src == '+')
		++src;
	if (!*src)
		arg->err = ERR_NOT_A_NUM;
	while ('0' <= *src && *src <= '9' && ui < (unsigned)(INT_MAX) + minus)
		ui = ui * 10 + *(src++) - '0';
	if (ui > (unsigned)INT_MAX + minus
			|| (ui == (unsigned)INT_MAX + minus && '0' <= *src && *src <= '9'))
		arg->err = ERR_TOO_BIG;
	else if (*src != '\0')
		arg->err = ERR_NOT_A_NUM;
	if (minus == 1)
		return (-ui);
	return (ui);
}

int	arg_set_error(t_argument *arg, int err, int ac_err)
{
	arg->err = err;
	arg->i = ac_err;
	return (FAILURE);
}

int	parse_cor(t_argument *arg, char *s, int *i)
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

int	parse_dump(t_argument *arg, int *i)
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

int	parse_n(t_argument *arg, int *i)
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

int	argument_parser(t_argument *arg)
{
	char	*s;
	int		ret;
	
	arg->i = 0;
	while (++(arg->i) < arg->ac)
	{
		if (!ft_strcmp(arg->av[(arg->i)], "-dump"))
			ret = parse_dump(arg, &(arg->i));
		else if (!ft_strcmp(arg->av[(arg->i)], "-n"))
			ret = parse_n(arg, &(arg->i));
		else if ((s = ft_strrstr(arg->av[(arg->i)], FILE_EXT)))
			ret = parse_cor(arg, s, &(arg->i));
		else
			ret = arg_set_error(arg, ERR_INVALID, arg->i);
		if (ret == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
