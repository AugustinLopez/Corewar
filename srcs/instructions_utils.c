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

void		insert_instructions(t_instruction ins, size_t pc, t_vm *vm)
{
	if (ins.op == 16) // 1 ARG (no mask)
		ins.p[0] = vm->ram[pc + 1].byte;
	else if (ins.op ==  1 || ins.op == 9 || ins.op == 12 || ins.op == 15) // 1 ARG (no mask)
	{
		if (ins.op == 1)
			ins.p[0] = ((vm->ram[pc + 1].byte << 24) | (vm->ram[pc + 2].byte << 16)
				| (vm->ram[pc + 3].byte << 8) | (vm->ram[pc + 4].byte));
		else if (ins.op == 9 || ins.op == 12 || ins.op == 15)
			ins.p[0] = ((vm->ram[pc + 1].byte << 8) | (vm->ram[pc + 2].byte));
	}
	else if (ins.op == 2 || ins.op == 3 || ins.op ==  13) // 2 ARG (mask pc+1)
	{
		if (ins.op == 2 || ins.op == 13) // ld et lld
		{
			if (ins.ocp == 3) // cas UND, REG
			{
				ins.p[0] = ((vm->ram[pc + 2].byte << 8) | vm->ram[pc + 3].byte);
				ins.p[1] = vm->ram[pc + 4].byte;
			}
			else if (ins.ocp == 5) // cas DIR, REG
			{
			ins.p[0] = ((vm->ram[pc + 2].byte << 24) | (vm->ram[pc + 3].byte << 16)
			| (vm->ram[pc + 4].byte << 8) | (vm->ram[pc + 5].byte));
			ins.p[1] = vm->ram[pc + 6].byte;
			}
		}
		else if (ins.op == 3) // st
		{
			if (ins.ocp == 3) // cas REG, IND
			{
				ins.p[0] = vm->ram[pc + 2].byte;
				ins.p[1] = ((vm->ram[pc + 3].byte << 8) | vm->ram[pc + 4].byte);
			}
			else if (ins.ocp == 5) // cas REG, REG
			{
				ins.p[0] = vm->ram[pc + 2].byte;
				ins.p[1] = vm->ram[pc + 3].byte;
			}
		}
	}
	else if (ins.op == 4 || ins.op == 5 || ins.op == 6 || ins.op == 7 || ins.op == 8 || ins.op == 10
	|| ins.op == 11 || ins.op ==  14) // 3 ARG (mask pc+1)
	{
		if (ins.op == 4 || ins.op == 5) // add, sub
		{
			ins.p[0] = vm->ram[pc + 2].byte;
			ins.p[1] = vm->ram[pc + 3].byte;
			ins.p[2] = vm->ram[pc + 4].byte;
		}
		else if (ins.op == 6 || ins.op == 7 || ins.op == 8) // and, or, xor
		{
			if (ins.ocp == 3) // cas REG, REG, REG
			{
			ins.p[0] = vm->ram[pc + 2].byte;
			ins.p[1] = vm->ram[pc + 3].byte;
			ins.p[2] = vm->ram[pc + 4].byte;
			}
			else if (ins.ocp == 4) // cas REG, IND, REG ou IND, REG, REG
			{
				if (vm->ram[pc + 1].byte == 0x74) // mask pour REG, IND, REG
				{
					ins.p[0] = vm->ram[pc + 2].byte;
					ins.p[1] = ((vm->ram[pc + 3].byte << 8) | (vm->ram[pc + 4].byte));
					ins.p[2] = vm->ram[pc + 5].byte;
				}
				else if(vm->ram[pc + 1].byte == 0xD4) // mask pour IND, REG, REG
				{
					ins.p[0] = ((vm->ram[pc + 2].byte << 8) | (vm->ram[pc + 3].byte));
					ins.p[1] = vm->ram[pc + 4].byte;
					ins.p[2] = vm->ram[pc + 5].byte;
				}
			}
			else if (ins.ocp == 5) // cas IND, IND, REG
			{
				ins.p[0] = ((vm->ram[pc + 2].byte << 8) | vm->ram[pc + 3].byte);
				ins.p[1] = ((vm->ram[pc + 4].byte << 8) | vm->ram[pc + 5].byte);
				ins.p[2] = vm->ram[pc + 6].byte;
			}
			else if (ins.ocp == 6) // cas REG, DIR, REG ou DIR, REG, REG
			{
				if (vm->ram[pc + 1].byte == 0x64) // mask pour REG, DIR, REG
				{
					ins.p[0] = vm->ram[pc + 2].byte;
					ins.p[1] = ((vm->ram[pc + 3].byte << 24) | (vm->ram[pc + 4].byte << 16)
						| (vm->ram[pc + 5].byte << 8) | (vm->ram[pc + 6].byte));
					ins.p[2] = vm->ram[pc + 7].byte;
				}
				else if(vm->ram[pc + 1].byte == 0x94) // mask pour DIR, REG, REG
				{
					ins.p[0] = ((vm->ram[pc + 2].byte << 24) | (vm->ram[pc + 3].byte << 16)
						| (vm->ram[pc + 4].byte << 8) | (vm->ram[pc + 5].byte));
					ins.p[1] = vm->ram[pc + 6].byte;
					ins.p[2] = vm->ram[pc + 7].byte;
				}
			}
			else if (ins.ocp == 7) // cas  DIR, IND, REG ou IND, DIR, REG
			{
				if (vm->ram[pc + 1].byte == 0xB4) // mask pour DIR, IND, REG
				{
					ins.p[0] = ((vm->ram[pc + 2].byte << 24) | (vm->ram[pc + 3].byte << 16)
						| (vm->ram[pc + 4].byte << 8) | (vm->ram[pc + 5].byte));
					ins.p[1] = ((vm->ram[pc + 6].byte << 8) | vm->ram[pc + 7].byte);
					ins.p[2] = vm->ram[pc + 8].byte;
				}
				else if(vm->ram[pc + 1].byte == 0xE4) // mask pour IND, DIR, REG
				{
					ins.p[0] = ((vm->ram[pc + 2].byte << 8) | vm->ram[pc + 3].byte);
					ins.p[1] = ((vm->ram[pc + 4].byte << 24) | (vm->ram[pc + 5].byte << 16)
						| (vm->ram[pc + 6].byte << 8) | (vm->ram[pc + 7].byte));
					ins.p[2] = vm->ram[pc + 8].byte;
				}
			}
			else if (ins.ocp == 9) // cas DIR, DIR, REG
			{
				ins.p[0] = ((vm->ram[pc + 2].byte << 24) | (vm->ram[pc + 3].byte << 16)
					| (vm->ram[pc + 4].byte << 8) | (vm->ram[pc + 5].byte));
				ins.p[1] = ((vm->ram[pc + 6].byte << 24) | (vm->ram[pc + 7].byte << 16)
					| (vm->ram[pc + 8].byte << 8) | (vm->ram[pc + 9].byte));
				ins.p[2] = vm->ram[pc + 10].byte;
			}
		}
		else if (ins.op == 10 || ins.op == 14) // ldi, lldi __(! DIR sur 2 bytes !)__
		{
			if (ins.ocp == 3) // cas REG, REG, REG
			{
				ins.p[0] = vm->ram[pc + 2].byte;
				ins.p[1] = vm->ram[pc + 3].byte;
				ins.p[2] = vm->ram[pc + 4].byte;
			}
			else if (ins.ocp == 4) // cas (1. REG, DIR, REG) ou (2. DIR, REG, REG ou IND, REG, REG)
			{
				if (vm->ram[pc + 1].byte == 0x19) // mask 1, 2, 1
				{
					ins.p[0] = vm->ram[pc + 2].byte;
					ins.p[1] = ((vm->ram[pc + 3].byte << 8) | vm->ram[pc + 4].byte);
					ins.p[2] = vm->ram[pc + 5].byte;
				}
				else if(vm->ram[pc + 1].byte == 0x25 || vm->ram[pc + 1].byte == 0x35) // masks 2, 1, 1
				{
					ins.p[0] = ((vm->ram[pc + 2].byte << 8) | vm->ram[pc + 3].byte);
					ins.p[1] = vm->ram[pc + 4].byte;
					ins.p[2] = vm->ram[pc + 5].byte;
				}
			}
			else if (ins.ocp == 5) //cas IND, DIR, REG ou DIR, IND, REG
			{
				ins.p[0] = ((vm->ram[pc + 2].byte << 8) | vm->ram[pc + 3].byte);
				ins.p[1] = ((vm->ram[pc + 4].byte << 8) | vm->ram[pc + 5].byte);
				ins.p[2] = vm->ram[pc + 6].byte;
			}
		}
		else if (ins.op == 11) // sti __(! DIR sur 2 bytes !)__
		{
			if (ins.ocp == 3) // cas REG, REG, REG
			{
				ins.p[0] = vm->ram[pc + 2].byte;
				ins.p[1] = vm->ram[pc + 3].byte;
				ins.p[2] = vm->ram[pc + 4].byte;
			}
			else if (ins.ocp == 4) // cas (1. REG, REG, DIR) ou (2. REG, DIR, REG ou REG, IND, REG)
			{
				if (vm->ram[pc + 1].byte == 0x19) // mask 1, 1, 2
				{
					ins.p[0] = vm->ram[pc + 2].byte;
					ins.p[1] = vm->ram[pc + 3].byte;
					ins.p[2] = ((vm->ram[pc + 4].byte << 8) | vm->ram[pc + 5].byte);
				}
				else if(vm->ram[pc + 1].byte == 0x25 || vm->ram[pc + 1].byte == 0x35) // masks 1, 2, 1
				{
					ins.p[0] = vm->ram[pc + 2].byte;
					ins.p[1] = ((vm->ram[pc + 3].byte << 8) | vm->ram[pc + 4].byte);
					ins.p[2] = vm->ram[pc + 5].byte;
				}
			}
			else if (ins.ocp == 5) //cas REG, IND, DIR ou REG, DIR, IND
			{
				ins.p[0] = vm->ram[pc + 2].byte;
				ins.p[1] = ((vm->ram[pc + 3].byte << 8) | vm->ram[pc + 4].byte);
				ins.p[2] = ((vm->ram[pc + 5].byte << 8) | vm->ram[pc + 6].byte);
			}
		}
	}
}

int		mask_in_byte(uint8_t op, uint8_t byte)
{
	if (byte == 1)
		return (1);
	else if (byte == 2)
		return ((op == 10 || op == 11 || op == 14) ? 2 : 4);
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
	if (op == 0)
		return (-1);;
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
	/*
	else if (op == 2 || op == 3 || op == 13) //2 ARG == 2 (mask pc+1)
	{
		if ((sum = (next_byte & 0xC0) >> 6) == 0)
			return (-1);
		jump_size = mask_in_byte(op, sum);
		if ((sum = (next_byte & 0x30) >> 4) == 0)
			return (-1);
		jump_size += mask_in_byte(op, sum);
	}
	else //3 ARG == 3 (mask pc+1)
	{
		if ((sum = (next_byte & 0xC0) >> 6) == 0)
			return (-1);
		jump_size = mask_in_byte(op, sum);
		if ((sum = (next_byte & 0x30) >> 4) == 0)
			return (-1);
		jump_size += mask_in_byte(op, sum);
		if ((sum = (next_byte & 0xC) >> 2) == 0)
			return (-1);
		jump_size += mask_in_byte(op, sum);
	}
	*/
	return (jump_size);
}

int main(int ac, char **av)
{
	uint8_t	i;
	uint8_t	j;
	uint8_t	ocp;

	ocp = 0;
	if (ac == 3)
	{
		j = ft_atoi(av[2]);
		i = ft_atoi(av[1]);
		ocp = encode_op_to_ocp(i, j);
		ft_printf("binaire du mask %08b\n", j);
		ft_printf("DIR_CODE = 2\n");
		ft_printf("IND_CODE = 3\n");
		ft_printf("REG_CODE = 1\n\n");
		if (ocp != 255)
			ft_printf("op_code = %d  |  dec value of mask = %d ==> %d\n", i, j, ocp);
		else
			ft_printf("op_code = %d  |  dec value of mask = %d ==> %s\n", i, j, "ERROR");
	}
	else
		ft_printf("ARG 1 = OP \nARG 2 = dec value of mask\n");
}
