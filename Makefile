# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 14:31:41 by aulopez           #+#    #+#              #
#    Updated: 2019/09/23 14:31:59 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM=asm
NAME_VM=corewar
COMPILER=gcc
FLAGS=-g3 -O3 -fno-builtin -Wall -Wextra
CC_OBJ=gcc $(FLAGS) -MMD -MP -c -I$(PATH_HDR)
CC_EXE=gcc $(FLAGS) -I$(PATH_HDR) -L$(PATH_LIB)

# --- 1.Source/Header ----------------------------------------------------------

SOURCE_ASM=asm_main
SOURCE_VM=	vm_main \
			vm_parser_main		\
			vm_parser_argv		\
			vm_parser_argv_2	\
			vm_parser_file		\
			vm_parser_file_2	\
			vm_ram				\
			vm_process			\
			vm_player			\
			op_live				\
			op_zjmp				\
			op_ld				\
			op_ldi				\
			op_fork				\
			op_arithmetic		\
			op_binary			\
			op_sti				\
			op_aff				\
			op_st
LIBFT=$(PATH_LIB)libft.a

# --- 2.Path/Object ------------------------------------------------------------

PATH_HDR=./includes/
PATH_LIB=./libft/
PATH_OBJ=./.object/
VPATH=srcs:srcs/parser:srcs/op

OBJ_ASM=$(SOURCE_ASM:%=$(PATH_OBJ)%.o)
OBJ_VM=$(SOURCE_VM:%=$(PATH_OBJ)%.o)
OBJ=$(OBJ_VM) $(OBJ_ASM)
DEPS=$(OBJ_VM:%.o=%.d)

# --- 4.Rules ------------------------------------------------------------------

all: $(LIBFT) $(NAME_VM)

$(NAME_ASM): $(OBJ_ASM)
	-@printf " ===> Creating $(NAME_ASM)\n"
	@$(CC_EXE) -o $(NAME_ASM) $(OBJ_ASM) -lft

$(NAME_VM): $(OBJ_VM)
	-@printf " ===> Creating $(NAME_VM)\n"
	@$(CC_EXE) -o $(NAME_VM) $(OBJ_VM) -lft

$(LIBFT):
	-@printf " ===> Creating $(LIBFT)\n"
	@make -C $(PATH_LIB)

$(PATH_OBJ)%.o:%.c
	-@printf " >O $(FLAGS) $*\n"
	@$(CC_OBJ) $< -o $@

clean:
	-@printf " ===> Removing object file(s)\n"
	@rm -f $(OBJ) $(DEPS)
	@make clean -C $(PATH_LIB) >> /dev/null

fclean: clean
	-@printf " ===> Removing $(NAME_ASM)\n"
	@rm -f $(NAME_ASM) $(NAME_VM)
	@make fclean -C $(PATH_LIB) >> /dev/null

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
