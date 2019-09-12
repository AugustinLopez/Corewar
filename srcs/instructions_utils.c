/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:53:57 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/12 18:47:49 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"

int		mask_in_byte(uint8_t op, uint8_t byte)
{
	if (byte == 1)
		return (1);
	else if (byte == 2)
		return ((op == 9 || op == 14 || op == 15) ? 2 : 4);
	else if (byte == 3)
		return (2);
	return (-1);
}

uint8_t	encode_op_to_ocp(uint8_t op, uint8_t next_byte)
{
	int sum;
	int jump_size;
	int	i;
	int	j;

	sum = 0;
	jump_size = 0;
	if (op == 1 || op == 9 || op == 12 || op == 15 || op == 16) //1 ARG
		return (0);
	i = 3;
	j = (op == 2 || op == 3 || op == 13) ? 1 : 0;
	while (i-- > j)
	{
		if ((sum = (next_byte & (0x3 << ((i + 1) * 2)))) == 0)
			return (-1);
		jump_size += mask_in_byte(op, sum >> ((i + 1) * 2));
	}
/*	else if (op == 2 || op == 3 || op == 13) //2 ARG == 2 mask
	{
		if ((sum = (next_byte & 0xC0) >> 6) == 0)
			return (-1);
		jump_size = mask_in_byte(sum);
		if ((sum = (next_byte & 0x30) >> 4) == 0)
			return (-1);
		jump_size += mask_in_byte(sum);
	}
	else //3 ARG == 3 mask
	{
		if ((sum = (next_byte & 0xC0) >> 6) == 0)
			return (-1);
		jump_size = mask_in_byte(sum);
		if ((sum = (next_byte & 0x30) >> 4) == 0)
			return (-1);
		jump_size += mask_in_byte(sum);
		if ((sum = (next_byte & 0xC) >> 2) == 0)
			return (-1);
		jump_size += mask_in_byte(sum);
	}*/
	return (jump_size);
}

int main(int ac, char **av)
{
	uint8_t	i;
	uint8_t	j;
	if (ac == 3)
	{
		j = ft_atoi(av[2]);
		i = ft_atoi(av[1]);

		ft_printf("%08b\n", j);
		ft_printf("DIR_CODE = 2\n");
		ft_printf("IND_CODE = 3\n");
		ft_printf("REG_CODE = 1\n\n");
		ft_printf("op_code = %d  |  dec value of mask = %d ==> %d\n", i, j
			,encode_op_to_ocp(i, j));
	}
	else
		ft_printf("ARG 1 = dec value of mask\nARG 2 = value of OP\n");
}
