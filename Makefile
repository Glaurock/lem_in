# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 08:23:52 by gmonnier          #+#    #+#              #
#    Updated: 2018/02/15 23:44:40 by fauconfan        ###   ########.fr        #
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
	io/input.c \
	io/input2.c \
	io/print_utils.c \
	model/edge.c \
	model/ants.c \
	model/graph.c \
	model/graph2.c \
	model/handle_neg_cycle.c \
	model/residual_graph.c \
	algo/new_algo_utils.c \
	algo/algo_utils.c \
	algo/find_path.c \
	utils/free_n_error.c \
	utils/transform.c \
	dfs.c \
	bfs.c \
	main.c \

LIB = ./libft/libft.a \

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
INCS = $(addprefix -I, $(addsuffix /, $(INCDIR)))

#Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_BLUE=\x1b[94m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(FLAGS) -o $@ $(LIB) -l m $(INCS)
	@printf "$(_BLUE)Compiling project $(NAME)...$(_GREEN)DONE$(_END)\n"

clean:
	@printf "$(_RED)Removed objects (.o) files.$(_END)\n"
	@make clean -C ./libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@printf "$(_RED)Removed project ($(NAME)).$(_END)\n"
	@make fclean -C ./libft
	@/bin/rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "                                                        \r"
	@printf "$(_BLUE)Compiling $@$(_END)\r"
	@$(CC) $(FLAGS) -c $? -o $@  $(INCS)

$(LIB):
	@make -C libft

test: all
	@./$(NAME) < test2.txt

other: all
	@./$(NAME) < lemin-tests/model_3
