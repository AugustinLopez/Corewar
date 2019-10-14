# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 14:31:41 by aulopez           #+#    #+#              #
#    Updated: 2019/10/14 18:10:28 by aulopez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM=asm
NAME_VM=corewar
COMPILER=gcc
FLAGS=-g3 -Wall -Wextra -Werror
CC_OBJ=gcc $(FLAGS) -MMD -MP -c -I$(PATH_HDR)
CC_EXE=gcc $(FLAGS) -I$(PATH_HDR) -L$(PATH_LIB)

# --- 1.Source/Header ----------------------------------------------------------

SOURCE_ASM=	asm					\
			write_cor			\
			ft_checkparam		\
			ft_free				\
			ft_getcode			\
			ft_getheader		\
			ft_init_s			\
			ft_isparam			\
			ft_read				\
			op					\
			tools_code			\
			tools_is			\
			tools_lst			\
			write_param			\
			ft_atol				\
			ft_atol_base		\
			ft_cpos				\
			ft_free_strtab		\
			ft_isblank			\
			ft_isint			\
			ft_islong			\
			ft_ismxdigit		\
			ft_ismxlong			\
			ft_isspace			\
			ft_joincstr			\
			ft_lconvert_base	\
			ft_ltoa				\
			ft_lutoa_base		\
			ft_str_is_mxdigit	\
			ft_str_is_numeric	\
			ft_strjfree			\
			ft_strsubfree		\
			ft_strtrimfree		\
			ft_strnjoin			\
			ft_reverse_bytes

SOURCE_VM=	vm_main				\
			vm_ram				\
			vm_dump				\
			vm_gameloop			\
			vm_process			\
			vm_player			\
			vm_parser_main		\
			vm_parser_argv		\
			vm_parser_argv_2	\
			vm_parser_file		\
			vm_parser_file_2	\
			op_live				\
			op_zjmp				\
			op_ld				\
			op_ldi				\
			op_fork				\
			op_arithmetic		\
			op_binary			\
			op_sti				\
			op_aff				\
			op_st				\
			op_bonus

LIBFT=$(PATH_LIB)libft.a

# --- 2.Path/Object ------------------------------------------------------------

PATH_HDR=./includes/
PATH_LIB=./libft/
PATH_OBJ=./.object/
VPATH=srcs:srcs/parser:srcs/op:srcs/minilib:srcs/assembly:

OBJ_ASM=$(SOURCE_ASM:%=$(PATH_OBJ)%.o)
OBJ_VM=$(SOURCE_VM:%=$(PATH_OBJ)%.o)
OBJ=$(OBJ_VM) $(OBJ_ASM)
DEPS=$(OBJ_VM:%.o=%.d)

# --- 4.Rules ------------------------------------------------------------------

all: $(LIBFT) $(NAME_ASM) $(NAME_VM)

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
	-@printf " >O $(FLAGS) -MMD -MP $*\n"
	@$(CC_OBJ) $< -o $@

clean:
	-@printf " ===> Removing object file(s)\n"
	@rm -f $(OBJ) $(DEPS)
	@make clean -C $(PATH_LIB) >> /dev/null

fclean: clean
	-@printf " ===> Removing $(NAME_ASM) $(NAME_VM)\n"
	@rm -f $(NAME_ASM) $(NAME_VM)
	@make fclean -C $(PATH_LIB) >> /dev/null

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
