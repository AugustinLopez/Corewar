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

size_t	my_atozu(t_argument *arg, const char *src)
{
	size_t	ui;
	size_t	limit;
	size_t	tmp;

	limit = -1;
	ui = 1;
	while ((limit /= 10))
		ui *= 10;
	tmp = -1;
	limit = ui / 10;
	ui = 0;
	if (*src == '+')
		++src;
	while ('0' <= *src && *src <= '9' && ui < limit)
		ui = ui * 10 + *(src++) - '0';
	if ('0' <= *src && *src <= '9')
	{
		if (ui > tmp / 10 || (ui == limit && (size_t)(*src - '0') > tmp % 10))
		{
			arg->err = ERR_TOO_BIG;
			return (-1);
		}
		ui = ui * 10 + *src++ - '0';
	}
	if (*src && ('0' <= *src && *src <= '9'))
		arg->err = ERR_TOO_BIG;
	else if (*src != '\0' || ui == 0)
		arg->err = ERR_NOT_A_NUM;
	return (ui);
}

int	set_error(t_argument *arg, int err, int ac_err)
{
	arg->err = err;
	arg->i = ac_err;
	return (FAILURE);
}

/*int	is_valid_number(t_argument *arg, char *str)
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
		{
			arg->err = ERR_NOT_A_NUM;
			return (FALSE);
		}
		i += 1;
		if (i > LOG_UINT64_MAX + 1)
		{
			arg->err = ERR_TOO_BIG;
			return (FALSE);
		}
	}
	if (i == j)
	{
		arg->err = ERR_NOT_A_NUM;
		return (FALSE);
	}
	return (TRUE);
}*/

int	parse_cor(t_argument *arg, char *s, int *i)
{
	if (s[4])
		return (set_error(arg, ERR_NOT_A_COR, *i));
	else if (arg->nbr_player >= MAX_PLAYERS)
		return (set_error(arg, ERR_TOO_MANY, *i));
	arg->file[arg->nbr_player] = arg->av[*i];
	arg->nbr_player += 1;
	return (SUCCESS);
}

int	parse_dump(t_argument *arg, int *i)
{
	if (arg->dump_option == TRUE)
		return (set_error(arg, ERR_TWO_DUMP, *i));
	arg->dump_option = TRUE;
	if (!((*i + 1) < arg->ac))
		return (set_error(arg, ERR_MISS_AV, *i + 1));
	if (arg->av[*i + 1][0] == '-')
		return (set_error(arg, ERR_NEGATIVE, *i + 1));
	arg->dump_value = my_atozu(arg, arg->av[++*i]);
	if (arg->err)
		return (FAILURE);
	return (SUCCESS);
}

int	my_atoi(t_argument *arg, const char *src)
{
	uint8_t			sign;
	unsigned long	ui;

	ui = 0;
	sign = (*src == '-') ? 1 : 0;
	if (sign == 1 || *src == '+')
		++src;
	while ('0' <= *src && *src <= '9' && ui - sign < INT_MAX)
		ui = ui * 10 + *(src++) - '0';
	if (ui == 0)
		arg->err = ERR_NOT_A_NUM;
	else if (ui - sign > INT_MAX && (!*src || ('0' <= *src && *src <= '9')))
		arg->err = ERR_TOO_BIG;
	else if (*src)
		arg->err = ERR_NOT_A_NUM;
	if (sign)
		return (-ui);
	return (ui);
}

int	parse_n(t_argument *arg, int *i)
{
	char	*s;

	if (!(*i + 1 < arg->ac))
		return (set_error(arg, ERR_MISS_AV, *i + 1));
	else if (!(*i + 2 < arg->ac))
		return (set_error(arg, ERR_MISS_AV, *i + 2));
	else if (!(s = ft_strrstr(arg->av[*i + 2], ".cor")) || s[4])
		return (set_error(arg, ERR_NOT_A_COR, *i + 2));
	else if (arg->nbr_player >= MAX_PLAYERS)
		return (set_error(arg, ERR_TOO_MANY, *i));
	arg->n_option[arg->nbr_player] = TRUE;
	arg->value[arg->nbr_player] = ft_atoi(arg->av[++*i]);
	if (arg->err)
		return (FAILURE);
	arg->file[arg->nbr_player] = arg->av[++*i];
	arg->nbr_player += 1;
	return (SUCCESS);
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
			ret = set_error(arg, ERR_INVALID, arg->i);
		if (ret == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
