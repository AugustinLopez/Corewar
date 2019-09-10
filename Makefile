# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aulopez <aulopez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/09 14:31:41 by aulopez           #+#    #+#              #
#    Updated: 2019/09/09 14:57:01 by bcarlier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_ASM=asm
NAME_VM=corewar
COMPILER=gcc
FLAGS=-Wall -Wextra -Werror
CC=gcc $(FLAGS)

# --- 1.Source/Header ----------------------------------------------------------

SOURCE_ASM=asm_main
SOURCE_VM=test
HEADER_ASM=libft
HEADER_VM=libft corewar op
LIBFT=$(PATH_LIB)libft.a

# --- 2.Path -------------------------------------------------------------------

PATH_HDR=./includes/
PATH_LIB=./libft/

PATH_ASM=./srcs/
SRC_ASM=$(SOURCE_ASM:%=$(PATH_ASM)%.c)
OBJ_ASM=$(SRC_ASM:%.c=%.o)
HDR_ASM=$(HEADER_ASM:%=$(PATH_HDR)%.h)

PATH_VM=./srcs/
SRC_VM=$(SOURCE_VM:%=$(PATH_VM)%.c)
OBJ_VM=$(SRC_VM:%.c=%.o)
HDR_VM=$(HEADER_VM:%=$(PATH_HDR)%.h)


# --- 4.Rules ------------------------------------------------------------------

all: $(LIBFT) $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): $(OBJ_ASM) $(HDR_ASM)
	-@printf " ===> Creating $(NAME_ASM)\n"
	@$(CC) -o $(NAME_ASM) -I$(PATH_HDR) $(OBJ_ASM) -L$(PATH_LIB) -lft

$(NAME_VM): $(OBJ_VM) $(HDR_VM)
	-@printf " ===> Creating $(NAME_VM)\n"
	@$(CC) -o $(NAME_VM) -I$(PATH_HDR) $(OBJ_VM) -L$(PATH_LIB) -lft

$(LIBFT):
	-@printf " ===> Creating $(LIBFT)\n"
	@make -C $(PATH_LIB)

%.o:%.c $(HDR_ASM) $(HDR_VM)
	-@printf " >O $(FLAGS) $@\n"
	@$(CC) -I$(PATH_HDR) -c $< -o $@ 

clean:
	-@printf " ===> Removing object file(s)\n"
	@rm -f $(OBJ_ASM) $(OBJ_VM)
	@make clean -C $(PATH_LIB) >> /dev/null

fclean: clean
	-@printf " ===> Removing $(NAME_ASM)\n"
	@rm -f $(NAME_ASM) $(NAME_VM)
	@make fclean -C $(PATH_LIB) >> /dev/null

re: fclean all

.PHONY: all clean fclean re
