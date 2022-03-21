# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburri <rburri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 07:42:29 by rburri            #+#    #+#              #
#    Updated: 2022/03/21 09:42:44 by rburri           ###   ########.fr        #
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

CFLAGS = -Wall -Wextra -Werror -g3

#-fsanitize=address

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L. -lft

RLINE		= -lreadline -L ~/.brew/Cellar/readline/8.1.2/lib

INC_RL		= -I ~/.brew/Cellar/readline/8.1.2/include

SRC = src

BLT = builtins

BIN = bin

$(shell mkdir -p $(BIN))

SOURCE = 	$(SRC)/main.c\
			$(SRC)/find_path.c\
			$(SRC)/get_cmd.c\
			$(SRC)/redir1.c\
			$(SRC)/redir2.c\
			$(SRC)/signals.c\
			$(SRC)/init.c\
			$(SRC)/free_all.c\
			$(SRC)/exec_cmd.c\
			$(SRC)/exec_cmd_hd.c\
			$(SRC)/char_chk.c\
			$(SRC)/token_find.c\
			$(SRC)/token_utils.c\
			$(SRC)/token_handler.c\
			$(SRC)/pipe_utils.c\
			$(SRC)/builtin_cd.c\
			$(SRC)/builtin_echo.c\
			$(SRC)/builtin_pwd.c\
			$(SRC)/builtin_env.c\
			$(SRC)/cmd_table.c\
			$(SRC)/env_utils.c\
			$(SRC)/env_utils2.c\
			$(SRC)/builtin_export.c\
			$(SRC)/builtin_unset.c\
			$(SRC)/exec_if_builtin.c\
			$(SRC)/replace_var_env.c\
			$(SRC)/heredoc.c\
			

		
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
