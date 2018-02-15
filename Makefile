# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 08:23:52 by gmonnier          #+#    #+#              #
#    Updated: 2018/02/12 08:24:43 by fauconfan        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all $(NAME) clean fclean re

NAME = lem-in

CC = gcc
FLAGS = -Wall -Wextra -Werror

SRCDIR = srcs
OBJDIR = obj
INCDIR = includes \
		 ./libft/includes

SRC = \
	main.c \
	graph.c \
	graph2.c \
	edge.c \
	input.c \
	algo_utils.c \
	dfs.c \
	divers.c \
	free_n_error.c \
	ants.c \
	transform.c \
	new_algo_utils.c \
	find_path.c \
	handle_neg_cycle.c \
	residual_graph.c \
	bfs.c

LIB = ./libft/libft.a \

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
INCS = $(addprefix -I, $(addsuffix /, $(INCDIR)))

#Colors
# _GREY=\x1b[30m
# _RED=\x1b[31m
# _GREEN=\x1b[32m
# _BLUE=\x1b[94m
# _CYAN=\x1b[36m
# _WHITE=\x1b[37m
# _END=\x1b[0m

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@ $(LIB) -l m $(INCS)
	echo "$(_BLUE)Compiling project $(NAME)...$(_GREEN)DONE$(_END)"

clean:
	echo "$(_RED)Removed objects (.o) files.$(_END)"
	make clean -C ./libft
	/bin/rm -f $(OBJS)

fclean: clean
	echo "$(_RED)Removed project ($(NAME)).$(_END)"
	make fclean -C ./libft
	/bin/rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR) || true
	printf "                                                        \r"
	printf " $(_BLUE)Compiling $@$(_END)\r"
	$(CC) $(FLAGS) -c $? -o $@  $(INCS)

$(LIB):
	make -C libft

test: all
	./$(NAME) < test2.txt

other: all
	./$(NAME) < lemin-tests/model_3
