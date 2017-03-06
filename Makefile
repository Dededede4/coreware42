# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gnebie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 05:33:14 by gnebie            #+#    #+#              #
#    Updated: 2017/03/06 05:33:16 by gnebie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean, fclean, re, all $(NAME) fall
.SUFFIXES :

CC = gcc
FLAGS = -Wall -Werror -Wextra
SPE_FLAGS =

COREWAR_NAME = corewar
ASM_NAME = asm
NAME = $(COREWAR_NAME) $(ASM_NAME)

COREWAR_DIR = ./VM/
ASM_DIR = ./compiler/

LIB = $(LIB_DIR)libft.a
LIB_DIR = ./shared/libft/

SRC =
SRC_DIR = ./srcs/

OBJ = $(SRC:.c=.o)
OBJ_DIR = ./objs/

INC = ./include/

all : $(NAME)

sall : $(LIB)
	rm -f $(COREWAR_NAME)
	rm -f $(ASM_NAME)
	@(cd $(COREWAR_DIR) && $(MAKE) $(COREWAR_NAME))
	cp $(COREWAR_DIR)$(COREWAR_NAME) ./
	@(cd $(ASM_DIR) && $(MAKE) $(ASM_NAME))
	cp $(ASM_DIR)$(ASM_NAME) ./

$(LIB) :
	@(cd $(LIB_DIR) && MAKE)

%.o : %.c

$(COREWAR_NAME) : $(LIB)
	@(cd $(COREWAR_DIR) && $(MAKE) $@)
	cp $(COREWAR_DIR)$(COREWAR_NAME) ./

$(ASM_NAME) : $(LIB)
	@(cd $(ASM_DIR) && $(MAKE) $@)
	cp $(ASM_DIR)$(ASM_NAME) ./

clean :
	(cd $(LIB_DIR) && $(MAKE) $@)
	(cd $(ASM_DIR) && $(MAKE) $@)
	(cd $(COREWAR_DIR) && $(MAKE) $@)

fclean : clean
	rm -f $(NAME)
	@(cd $(LIB_DIR) && $(MAKE) $@)
	@(cd $(ASM_DIR) && $(MAKE) $@)
	@(cd $(COREWAR_DIR) && $(MAKE) $@)

re : fclean all
