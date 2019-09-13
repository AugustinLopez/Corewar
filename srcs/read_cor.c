/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:40:40 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/12 18:47:41 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int		vm_set_error(t_vm *vm, int err, char *strerr)
{
	vm->err = err;
	vm->strerr = strerr;
	return (FAILURE);
}

int		read_player(t_argument *arg, t_vm *vm, int fd)
{
	char	buffer[PROG_NAME_LENGTH + MAGIC_LENGTH + 1];
	int		i;

	i = PROG_NAME_LENGTH + MAGIC_LENGTH;
	ft_bzero(buffer, sizeof(buffer));
	if (read(fd, buffer, i) != i)
		return (vm_set_error(vm, ERR_NAME, arg->file[vm->player_total]));
	if (ft_memcmp(buffer, STR_EXEC_MAGIC, MAGIC_LENGTH) != 0)
		return (vm_set_error(vm, ERR_MAGIC, arg->file[vm->player_total]));
	if (!(vm->player[vm->player_total].name = ft_strdup(buffer + MAGIC_LENGTH)))
		return (vm_set_error(vm, ERR_MEMORY, arg->file[vm->player_total]));
	return (SUCCESS);
}

int		read_comment(t_argument *arg, t_vm *vm, int fd)
{
	char	buffer[COMMENT_LENGTH + 1];
	int		i;

	i = PROG_NAME_LENGTH + MAGIC_LENGTH + DECAL_COMMENT;
	ft_bzero(buffer, sizeof(buffer));
	if (lseek(fd, DECAL_COMMENT, SEEK_CUR) != i
			|| read(fd, buffer, COMMENT_LENGTH) != COMMENT_LENGTH)
		return (vm_set_error(vm, ERR_COMMENT, arg->file[vm->player_total]));
	if (!(vm->player[vm->player_total].comment = ft_strdup(buffer)))
		return (vm_set_error(vm, ERR_MEMORY, arg->file[vm->player_total]));
	return (SUCCESS);
}

int		read_file(t_argument *arg, t_vm *vm, int fd)
{
	char	buffer[CHAMP_MAX_SIZE + 2];
	size_t	j;
	int		i;
	int		ret;

	i = PROG_NAME_LENGTH + COMMENT_LENGTH
		+ MAGIC_LENGTH + DECAL_COMMENT + DECAL_PROG;
	ft_bzero(buffer, sizeof(buffer));
	if (lseek(fd, DECAL_PROG, SEEK_CUR) != i
			|| (ret = read(fd, buffer, CHAMP_MAX_SIZE + 1)) < 0)
		return (vm_set_error(vm, ERR_CODE, arg->file[vm->player_total]));
	if (ret > CHAMP_MAX_SIZE)
		return (vm_set_error(vm, ERR_MAX_SIZE, arg->file[vm->player_total]));
	i = 0;
	j = vm->player_total * MEM_SIZE / arg->nbr_player;
	vm->ram[j].process = TRUE;
	while (i < ret)
	{
		j %= MEM_SIZE;
		vm->ram[j].player_last = vm->player[vm->player_total].id;
		vm->ram[j++].byte = (unsigned char)buffer[i++];
	}
	return (SUCCESS);
}

int		read_cor(t_argument *arg, t_vm *vm)
{
	int			fd;

	if ((fd = open(arg->file[vm->player_total], O_RDONLY)) < 0)
		return (vm_set_error(vm, ERR_OPEN, arg->file[vm->player_total]));
	else if (read_player(arg, vm, fd) == FAILURE)
		return (FAILURE);
	else if (read_comment(arg, vm, fd) == FAILURE)
		return (FAILURE);
	else if (read_file(arg, vm, fd) == FAILURE)
		return (FAILURE);
	if (close(fd))
		(void)vm_set_error(vm, ERR_CLOSE, arg->file[vm->player_total]);
	return (SUCCESS);
}
