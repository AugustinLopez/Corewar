//#HEADER 42

#include "libft.h"
#include "corewar.h"

int load_new_process(t_vm *vm, t_process *proc)
{
	uint8_t	ocp;

	// op doit etre == 0 pour rentrer dans cette fonction
	proc->op->op = vm->ram[pc].byte;
	// max ocp == 9,  si ocp vaut 0  c'est qu'on a une op a 1 ARG,
	// si erreur ocp vaut 255 pour l'instant (-1 sur uint8_t)
	if (9 >= (ocp = encode_op_to_cop(proc->op->op, vm->ram[pc + 1 % MEM_SIZE])) >= 0)
	{
		insert_instructions(proc->op, pc, &vm);
		proc->cycle_to_wait += g_op_tab[op - 1][5];
		return (SUCCESS);
	}
	return (FAILURE)
}
