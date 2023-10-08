# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 11:03:03 by laugarci          #+#    #+#              #
#    Updated: 2023/10/08 13:01:46 by laugarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = philo

SRC_DIR = src/
SRC_FILES = philo.c atol.c parse_input.c create_threads.c start_routine.c start_eat.c utils.c

OBJ_DIR = objs/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES = $(SRC_FILES:.c=.d)
DEPS = $(addprefix $(OBJ_DIR), $(DEP_FILES))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD #-fsanitize=thread
RM = rm -f
INCLUDE = -I ./inc/

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $@

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean:		clean
			$(RM) -r $(OBJ_DIR)
			$(RM) $(NAME)

re:			fclean all


-include $(DEPS)

.PHONY: all clean fclean re

