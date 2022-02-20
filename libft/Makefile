# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburri <rburri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 13:29:27 by rburri            #+#    #+#              #
#    Updated: 2022/01/24 07:16:00 by rburri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

####################################################################
# COLORS
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
####################################################################
NAME = libft.a

FILES = 	ft_atoi.c ft_isspace.c ft_putchar.c ft_putnbr.c ft_putstr.c \
			ft_bzero.c ft_strcat ft_strcmp.c ft_strcpy.c ft_strncpy.c \
			ft_calloc.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
			ft_isalnum.c ft_putchar_fd.c ft_split.c ft_strmapi.c \
			ft_isalpha.c ft_striteri.c ft_itoa.c ft_substr.c \
			ft_isascii.c ft_toupper.c ft_tolower.c ft_strjoin.c \
			ft_isdigit.c ft_strtrim.c ft_strrchr.c ft_strnstr.c \
			ft_isprint.c ft_strncmp.c ft_strlen.c ft_strlcpy.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
			ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
			get_next_line.c ft_atoi_base.c ft_itoa_base.c\
			ft_isupper.c ft_islower.c ft_memalloc.c\
			ft_free_split.c

			
OBJECTS =  $(FILES:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc -c $(FLAGS)

MAKEFLAGS += --silent

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc libft.a $(OBJECTS)
	@echo "$(GREEN)Make libft done$(RESET)"

%.o: %.c
	$(CC) $< -o $@ 
	
clean:
	/bin/rm -f $(OBJECTS)

fclean: clean
	/bin/rm -f  $(NAME)

re: fclean all

.PHONY:	all clean fclean re