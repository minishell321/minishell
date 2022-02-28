# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburri <rburri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 07:42:29 by rburri            #+#    #+#              #
#    Updated: 2022/02/28 14:44:07 by vbotev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################################################
# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
####################################################################
CC = gcc 

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L. -lft

RLINE		= -lreadline -L ~/.brew/Cellar/readline/8.1.2/lib

INC_RL		= -I ~/.brew/Cellar/readline/8.1.2/include

SRC = src

BIN = bin

$(shell mkdir -p $(BIN))

SOURCE = 	$(SRC)/main.c\
			$(SRC)/path.c\
			$(SRC)/redir.c\
			$(SRC)/signals.c\
			$(SRC)/init.c\
			$(SRC)/free_all.c\
			$(SRC)/exec_cmd.c\
			$(SRC)/char_chk.c\
			
			

		
OBJS = $(patsubst %,$(BIN)/%,$(notdir $(SOURCE:.c=.o)))

$(BIN)/%.o : $(SRC)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

${NAME}:	${OBJS}
			@make -C ${LIBFT_DIR}/
			@cp ${LIBFT_DIR}/$(LIBFT_A) .
			$(CC)  ${OBJS} $(LIBFT) $(RLINE) $(INC_RL) -o $(NAME)
			@echo "$(GREEN)$(NAME) sucessfully created$(RESET)"

clean:
		@rm -f $(OBJS)
		@make -C ${LIBFT_DIR} clean

fclean: clean
		@rm -f $(NAME)
		@rm -f $(LIBFT_A)
		@make -C ${LIBFT_DIR} fclean
	
re: fclean all

.PHONY: fclean re all clean bonus
