/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 10:30:28 by aulopez           #+#    #+#             */
/*   Updated: 2019/09/11 17:11:41 by aulopez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h>
# include <sys/types.h>
# include "op.h"

# define FALSE			0
# define TRUE			1

# define FAILURE		0
# define SUCCESS		1

typedef uint8_t			t_bool;

typedef struct			t_argument
{
	char				*file[MAX_PLAYERS];
	char				**av;
	size_t				dump_value;
	int					ac;
	int					i;
	int					value[MAX_PLAYERS];
	t_bool				n_option[MAX_PLAYERS];
	t_bool				dump_option;
	uint8_t				nbr_player;
}						t_argument;

/*
** parameters can be either 1, 2 or 4 bytes. Base operation takes up to
** 3 parameters
** Bonus: the encoding allow for up to 4 parameters for bonus operation.
*/

typedef struct			s_instruction
{
	uint32_t			p[4];
	uint8_t				id;
	uint8_t				encoding;
}						t_instruction;

/*
** At the very beginning, we read the 1st operation and set cycle_to_proceed.
** cycle_to_proceed: once we hit 0, we apply the operation. Then we
** read immediately the next operation.
** Note that we do not need to keep track of the id. But might as well.
** We could use a single-linked list, but keeping track of prev make
** freeing easier (process might crash)
** Bonus: We can keep track of the player that spawned the process.
** !!! REGISTER 1 IS r[0] !!!
*/

typedef struct			s_process
{
	t_instruction		op;
	size_t				pc;
	uint32_t			process_id;
	uint32_t			player_id;
	uint16_t			cycle_to_wait;
	uint16_t			r[REG_NUMBER];
	t_bool				carry;
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

/*
** Only the variable byte is mandatory, the rest is bonus.
*/

typedef struct			s_ram
{
	size_t				write_total;
	size_t				cycle_last;
	uint32_t			player_last;
	uint8_t				byte;
}						t_ram;

typedef struct			s_player
{
	size_t				live_since_check;
	size_t				live_total;
	char				*name;
	char				*comment;
	int32_t				id;
	t_bool				still_alive;
}						t_player;

/*
** We keep our ram in an array for faster iteration (compared to linked list).
** Careful not to forget looping.
** process_total != process_index. Process_index is the number of the next
** process to be spawn and it will only increase
** Process_total might be reduced if a process is destroyed (bonus ?).
*/

typedef struct			s_vm
{
	size_t				cycle_total;
	size_t				cycle_since_check;
	size_t				live_since_check;
	size_t				cycle_to_dump;
	size_t				cycle_to_die;
	size_t				process_total;
	size_t				process_index;
	t_player			player[MAX_PLAYERS];
	t_ram				ram[MEM_SIZE];
	t_process			*process;
	uint8_t				player_total;
}						t_vm;

int						parser(t_argument *arg);

#endif
