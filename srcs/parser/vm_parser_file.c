/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parser_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:40:40 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/19 14:00:31 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "corewar.h"
#include <unistd.h>
#include <fcntl.h>

static inline int	read_player(t_argument *arg, t_vm *vm, int fd)
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

static inline int	read_comment(t_argument *arg, t_vm *vm, int fd)
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
	vm->player[vm->player_total].still_alive = TRUE;
	return (SUCCESS);
}

static inline int	read_file(t_argument *arg, t_vm *vm, int fd)
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

static inline int	read_cor(t_argument *arg, t_vm *vm)
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
	if (close(fd) == -1)
	{
		vm_set_error(vm, ERR_CLOSE, arg->file[vm->player_total]);
		ft_dprintf(STDERR_FILENO, "Warning: file '%s':\n", vm->strerr);
		ft_dprintf(STDERR_FILENO, "Could not close file.\n");
		vm->err = 0;
		vm->strerr = NULL;
	}
	return (SUCCESS);
}

int					file_parser(t_vm *vm, t_argument *arg)
{
	size_t	pc;

	ft_bzero(vm, sizeof(*vm));
	vm_set_null_id(vm, arg);
	while (vm->player_total < arg->nbr_player)
	{
		vm->player[vm->player_total].id = arg->value[vm->player_total];
		if (read_cor(arg, vm) == FAILURE)
			return (FAILURE);
		pc = vm->player_total * MEM_SIZE / arg->nbr_player;
		if (create_process(vm, pc, vm->player[vm->player_total].id) == FAILURE)
		{
			vm->err = ERR_MEMORY;
			vm->strerr = arg->file[vm->player_total];
			return (FAILURE);
		}
		vm->process->pc = pc;
		vm->process->next_pc = pc;
		vm->process->r[0] = (vm->player[vm->player_total]).id;
		vm->player_total += 1;
	}
	return (SUCCESS);
}
