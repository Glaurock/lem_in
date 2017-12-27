# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/02 08:23:52 by gmonnier          #+#    #+#              #
#    Updated: 2017/12/26 23:07:53 by gmonnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all $(NAME) clean fclean re

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = srcs
OBJDIR = obj
INCDIR = includes

SRC = \
	other/ft_swap_ptr.c \
	other/die.c \
	other/mallcheck.c

SRC += \
	test/ft_isalnum.c \
	test/ft_isalpha.c \
	test/ft_isascii.c \
	test/ft_isdigit.c \
	test/ft_isprint.c \
	test/ft_ischarset.c

SRC += \
	math/ft_recursive_power.c \
	math/ft_atoi.c \
	math/ft_itoa.c \
	math/ft_itoa_base.c

SRC += \
	print/ft_print_bits.c \
	print/ft_putchar.c \
	print/ft_putchar_fd.c \
	print/ft_putendl.c \
	print/ft_putendl_fd.c \
	print/ft_putnbr.c \
	print/ft_putnbr_fd.c \
	print/ft_putstr.c \
	print/ft_putstr_fd.c

SRC += \
	mem/ft_memalloc.c \
	mem/ft_memccpy.c \
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memdel.c \
	mem/ft_memmove.c \
	mem/ft_bzero.c \
	mem/ft_memset.c


SRC += \
	list/ft_lst_sort.c \
	list/ft_lst_pop.c \
	list/ft_lst_size.c \
	list/ft_lst_reverse.c \
	list/ft_lstadd.c \
	list/ft_lstdel.c \
	list/ft_lstdelone.c \
	list/ft_lstiter.c \
	list/ft_lstmap.c \
	list/ft_lstnew.c \
	list/ft_merge_sort.c

SRC += \
	str/ft_parse_char.c \
	str/ft_parse_str.c \
	str/ft_tolower.c \
	str/ft_toupper.c \
	str/ft_strcat.c \
	str/ft_strchr.c \
	str/ft_strclr.c \
	str/ft_strcmp.c \
	str/ft_strcpy.c \
	str/ft_strdel.c \
	str/ft_strdup.c \
	str/ft_strequ.c \
	str/ft_striter.c \
	str/ft_striteri.c \
	str/ft_strjoin.c \
	str/ft_strlcat.c \
	str/ft_strlen.c \
	str/ft_strmap.c \
	str/ft_strmapi.c \
	str/ft_strncat.c \
	str/ft_strncmp.c \
	str/ft_strncpy.c \
	str/ft_strnequ.c \
	str/ft_strnew.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_strsplit.c \
	str/ft_strstr.c \
	str/ft_strsub.c \
	str/ft_strtrim.c

SRC += \
	get_next_line.c

SRC += \
	ft_printf/analyse.c \
	ft_printf/arg.c \
	ft_printf/check_colors.c \
	ft_printf/ft_itoa_x.c \
	ft_printf/ft_wchar.c \
	ft_printf/get_str.c \
	ft_printf/get_str_nb.c \
	ft_printf/handle_sign_sharp.c \
	ft_printf/handle_width_prec.c \
	ft_printf/loop.c \
	ft_printf/preset.c \
	ft_printf/print.c \
	ft_printf/printf_family.c \
	ft_printf/utils.c

#Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[94m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SRC))))
ALL_OBJ_DIR = $(sort $(dir $(OBJS)))
INCS = $(addprefix -I, $(addsuffix /, $(INCDIR)))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(_BLUE)\nCompiling library $(NAME)... $(_GREEN)DONE$(_END)"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(ALL_OBJ_DIR) || true
	@printf "                                                          \r"
	@printf "$(_BLUE)Compiling $@$(_END)\r"
	@$(CC) -o $@ -c $(CFLAGS) $< $(INCS)

clean:
	@echo "$(_RED)Removed objects (.o) files.$(_END)"
	@/bin/rm -f $(OBJS)

fclean: clean
	@echo "$(_RED)Removed library ($(NAME)).$(_END)"
	@/bin/rm -f $(NAME)

re: fclean all
