/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_argv_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:39:53 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/16 11:53:48 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "libft.h"
#include <limits.h>

size_t					arg_atozu(t_argument *arg, const char *src)
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

int						arg_atoi(t_argument *arg, const char *src)
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

int						arg_set_error(t_argument *arg, int err, int ac_err)
{
	arg->err = err;
	arg->i = ac_err;
	return (FAILURE);
}

static inline int		set_id_for_no_n_option(t_argument *arg)
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

int						handle_duplicate_id(t_argument *arg)
{
	int	i;
	int	j;
	int	id;

	id = set_id_for_no_n_option(arg);
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
