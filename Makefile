# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laugarci <laugarci@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 11:03:03 by laugarci          #+#    #+#              #
#    Updated: 2023/07/31 09:39:36 by laugarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src/

SRC_FILES = philo.c atol.c parse_input.c create_philo.c create_threads.c

OBJ_DIR = objs/

OBJ_FILES = $(SRC_FILES:.c=.o)

OBJS = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

DEP_FILES = $(SRC_FILES:.c=.d)

DEPS = $(addprefix $(OBJ_DIR), $(DEP_FILES))

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD -pthread

RM = rm -f

INCLUDE = -I ./inc/

all:	$(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
			$(CC) $(OBJS) -o $@

$(OBJ_DIR):
			@mkdir $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS)
			$(RM) $(DEPS)
			rmdir $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

git:	fclean
	@git add .
	@git commit -m "philo"
	@git push


-include $(DEPS)

.PHONY: all clean fclean re git
