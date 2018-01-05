# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 08:23:52 by gmonnier          #+#    #+#              #
#    Updated: 2018/01/05 11:24:58 by gmonnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all $(NAME) clean fclean re

NAME = lem-in

CC = gcc
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRCDIR = srcs
OBJDIR = obj
INCDIR = includes \
		 ./libft/includes

SRC = \
	main.c \
	graph.c \
	node_utils.c \
	input.c \
	dijkstra.c \
	algo_utils.c \
	dfs.c \
	divers.c \
	free_n_error.c \
	ants.c \
	transform.c \
	new_algo_utils.c \
	find_path.c

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
	@$(CC) $(OBJS) $(FLAGS) $(LIB) $(MLXFLAGS) $(MLXFLAGS_MAC) $(MATHFLAG) -o $@
	@echo "$(_BLUE)Compiling project $(NAME)...$(_GREEN)DONE$(_END)"

clean:
	@echo "$(_RED)Removed objects (.o) files.$(_END)"
	@make clean -C ./libft
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "$(_RED)Removed project ($(NAME)).$(_END)"
	@make fclean -C ./libft
	@/bin/rm -f $(NAME)

re: fclean all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) || true
	@printf "                                                        \r"
	@printf " $(_BLUE)Compiling $@$(_END)\r"
	@$(CC) -o $@ -c $(FLAGS) $< $(INCS)

$(LIB):
	make -C $(@D)

test: all
	./$(NAME) < test2.txt

other: all
	./$(NAME) < lemin-tests/model_3
