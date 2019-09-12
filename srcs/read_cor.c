/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:40:40 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/12 13:03:19 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../libft/includes/libft.h"
#include "libft.h"
#include "corewar.h"

//for open, read, free
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int		read_cor(t_argument *arg, t_vm *vm, int p_nb)
{
	char		buffer[2049];
	size_t		i;
	int			fd;
	int			ret;

	i = 0;
	ft_bzero(buffer, sizeof(buffer));
	if ((fd = open(arg->file[p_nb], O_RDONLY)) < 0)
		return (FAILURE);
	ret = read(fd, buffer, 132);
	if (ft_memcmp(buffer, "\0\xea\x83\xf3", 4) != 0)
		return (FAILURE);
	if(!(vm->player[p_nb].name = ft_strdup(buffer + 4))) // protect name, mem alloc
	{
		free(vm->player[p_nb].name);
		return (FAILURE);
	}
	ft_bzero(buffer, sizeof(buffer));
	if ((ret = lseek(fd, 8, SEEK_CUR)) < 0)
		return (FAILURE);
	if ((ret = read(fd, buffer, 2048)) < 0)
		return (FAILURE);
	if (!(vm->player[p_nb].comment = ft_strdup(buffer)))
	{
		free(vm->player[p_nb].comment);
		return (FAILURE);
	}
	ft_bzero(buffer, sizeof(buffer));
	if ((ret = lseek(fd, 4, SEEK_CUR)) < 0)
		return (FAILURE);
	if ((ret = read(fd, buffer, CHAMP_MAX_SIZE + 1)) < 0)
		return (FAILURE);
	if (ret == CHAMP_MAX_SIZE + 1)
		return (FAILURE);
	else
	{
		i = 0;
		size_t	zu = p_nb * MEM_SIZE / vm->player_total;
		while (i < ret)
		{
			if (zu % 16 == 16 - 1)
				vm->ram[zu].byte = (unsigned char)buffer[i];
			else
				vm->ram[zu].byte =  (unsigned char)buffer[i];
			++i;
			++zu;
		}
	}
	close(fd);
	return (SUCCESS);
}

/*int	main(int ac, char **av)
{
	int i;
	int j;
	t_vm vm;
	char	*name;
	char	*comment;
	char	buffer[2049];
	size_t	pc;
	int		fd;
	int		ret;

	pc = 0;
	if (ac < 2)
		return (FAILURE);
	ft_bzero(&vm, sizeof(vm));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (FAILURE);
	i = 0;
	ft_bzero(buffer, sizeof(buffer));
	ret = read(fd, buffer, 132);
	if (ft_memcmp(buffer, "\0\xea\x83\xf3", 4) != 0)
		return (FAILURE);
	if(!(name = ft_strdup(buffer + 4))) // protect name, mem alloc
		return (FAILURE);
	ft_bzero(buffer, sizeof(buffer));
	if ((ret = lseek(fd, 8, SEEK_CUR)) < 0)
		return (FAILURE);
	if ((ret = read(fd, buffer, 2048)) < 0)
		return (FAILURE);
	if (!(comment = ft_strdup(buffer)))
		return (FAILURE);
	if ((ret = lseek(fd, 4, SEEK_CUR)) < 0)
		return (FAILURE);
	if ((ret = read(fd, buffer, CHAMP_MAX_SIZE + 1)) < 0)
		return (FAILURE);
	if (ret == CHAMP_MAX_SIZE + 1)
		return (FAILURE);
	else
	{
		i = 0;
		while (i < ret)
		{
			if (i % 16 == 16 - 1)
				vm.ram[pc + i].byte = (unsigned char)buffer[i];
			else
				vm.ram[pc + i].byte =  (unsigned char)buffer[i];
			++i;
		}
	}
	close(fd);
	dump_memory(&vm, 64);
	ft_printf("\n|%s|\n", name);
	ft_printf("comment : |%s|\n", comment);
	return (SUCCESS);
}*/
