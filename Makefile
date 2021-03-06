# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fauconfan <fauconfan@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 08:23:52 by gmonnier          #+#    #+#              #
#    Updated: 2018/10/01 08:27:29 by jpriou           ###   ########.fr        #
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
	algo/dfs.c \
	algo/bfs.c \
	utils/free_n_error.c \
	utils/transform.c \
	utils/math_utils.c \
	main.c \

LIB = ./libft/libft.a \

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
INCS = $(addprefix -I, $(addsuffix /, $(INCDIR)))

#Colors
_RED=$(shell tput setaf 1 2> /dev/null || echo "")
_GREEN=$(shell tput setaf 2 2> /dev/null || echo "")
_YELLOW=$(shell tput setaf 3 2> /dev/null || echo "")
_BLUE=$(shell tput setaf 4 2> /dev/null || echo "")
_PURPLE=$(shell tput setaf 5 2> /dev/null || echo "")
_CYAN=$(shell tput setaf 6 2> /dev/null || echo "")
_WHITE=$(shell tput setaf 7 2> /dev/null || echo "")
_END=$(shell tput sgr0 2> /dev/null || echo "")

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(OBJS) $(FLAGS) -o $@ $(LIB) $(INCS)
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
