

####################################################################
# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
####################################################################
CC = gcc 

NAME = minishell

FLAGS = -Wall -Wextra -Werror -g3

LIBFT_DIR	= libft
LIBFT_A		= libft.a
LIBFT		= -L. -lft

RLINE		= -lreadline

SRC = src

BIN = bin

$(shell mkdir -p $(BIN))

SOURCE = 	$(SRC)/main.c\

		
OBJS = $(patsubst %,$(BIN)/%,$(notdir $(SOURCE:.c=.o)))

$(BIN)/%.o : $(SRC)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

${NAME}:	${OBJS}
			@make -C ${LIBFT_DIR}/
			@cp ${LIBFT_DIR}/$(LIBFT_A) .
			$(CC)  ${OBJS} $(LIBFT) $(RLINE) -o $(NAME)
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
