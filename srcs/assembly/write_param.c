/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algautie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:13:10 by algautie          #+#    #+#             */
/*   Updated: 2019/10/11 15:28:17 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../includes/op.h"

static unsigned int	ft_atou(const char *str)
{
	int				i;
	unsigned int	nb;

	i = 0;
	nb = 0;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '%'))
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

static int			ft_hexatoi(char *nbr, int *skip)
{
	int				ret;
	int				i;

	ret = 0;
	i = *skip;
	if (ft_isdigit(nbr[i]))
		ret += nbr[i] - '0';
	else if (nbr[i] >= 'A' && nbr[i] <= 'F')
		ret += nbr[i] - 'A' + 10;
	if (!nbr[i] || !nbr[i + 1] || (ft_strlen(nbr) % 2 - *skip == 1
			&& ++(*skip)))
		return (ret);
	else
		ret *= 16;
	i++;
	if (ft_isdigit(nbr[i]))
		ret += nbr[i] - '0';
	else if (nbr[i] >= 'A' && nbr[i] <= 'F')
		ret += nbr[i] - 'A' + 10;
	*skip += 2;
	return (ret);
}

static void			split_param(unsigned int address, int parts, t_struct *s)
{
	char	*nbr;
	int		len;
	int		skip;

	skip = 0;
	if (!(nbr = ft_lutoa_base((uint64_t)address, 16, 'A')))
		ft_error(s, MALL_ERR, -1);
	len = ft_strlen(nbr);
	len += (len % 2 == 1 ? 1 : 0);
	s->index += (parts - (len / 2));
	while (len > 0)
	{
		s->prog[s->index] = ft_hexatoi(nbr, &skip);
		s->index++;
		len -= 2;
	}
	if (nbr)
		free(nbr);
}

static unsigned int	get_label(t_struct *s, char *param)
{
	int				i;
	unsigned int	ret;
	t_label			*tmp;

	i = 0;
	ret = 0;
	tmp = s->lab;
	while (param[i] == '%' || param[i] == ':')
		i++;
	while (tmp && ft_strcmp(tmp->name, param + i))
		tmp = tmp->next;
	if (!tmp)
	{
		ft_dprintf(STDERR_FILENO
				, "%sError: Label '%s' does not exist\n%s"
				, FT_RED, param + i, FT_EOC);
		ft_free_s(s);
		exit(-1);
	}
	if (tmp->address - s->last_opcode >= 0)
		ret = tmp->address - s->last_opcode;
	else
		ret = 0xFFFFFFFF - s->last_opcode + tmp->address + 1;
	return (ret);
}

void				write_param(t_struct *s, char *param, int opc)
{
	unsigned int	address;

	if ((param[0] && param[0] == ':') || (param[1] && param[1] == ':'))
		address = get_label(s, param);
	else
		address = ft_atou(param);
	if (ft_isreg(param))
		s->prog[s->index++] = ft_atou(param + 1);
	else if (ft_isdir(param) && is_four_dir(opc))
		split_param(address, 4, s);
	else
		split_param((unsigned short)address, 2, s);
}
