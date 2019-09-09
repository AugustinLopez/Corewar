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
COMPILER=gcc
FLAGS=-Wall -Wextra -Werror
CC=gcc $(FLAGS)

# --- 1.Source/Header ----------------------------------------------------------

SOURCE_ASM=asm_main
HEADER_ASM=libft
LIBFT=$(PATH_LIB)libft.a

# --- 2.Path -------------------------------------------------------------------

PATH_HDR=./includes/
PATH_LIB=./libft/
PATH_ASM=./srcs/
SRC_ASM=$(SOURCE_ASM:%=$(PATH_ASM)%.c)
OBJ_ASM=$(SRC_ASM:%.c=%.o)
HDR_ASM=$(HEADER_ASM:%=$(PATH_HDR)%.h)

# --- 4.Rules ------------------------------------------------------------------

all: $(LIBFT) $(NAME_ASM)

$(NAME_ASM): $(OBJ_ASM) $(HDR_ASM)
	-@printf " ===> Creating $(NAME_ASM)\n"
	@$(CC) -o $(NAME_ASM) -I$(PATH_HDR) $(OBJ_ASM) -L$(PATH_LIB) -lft

$(LIBFT):
	-@printf " ===> Creating $(LIBFT)\n"
	@make -C $(PATH_LIB)

%.o:%.c $(HDR_ASM)
	-@printf " >O $(FLAGS) $@\n"
	@$(CC) -I$(PATH_HDR) -c $< -o $@ 

clean:
	-@printf " ===> Removing object file(s)\n"
	@rm -f $(OBJ_ASM)
	@make clean -C $(PATH_LIB) >> /dev/null

fclean: clean
	-@printf " ===> Removing $(NAME_ASM)\n"
	@rm -f $(NAME_ASM)
	@make fclean -C $(PATH_LIB) >> /dev/null

re: fclean all

.PHONY: all clean fclean re
