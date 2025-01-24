# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 09:18:13 by bchallat          #+#    #+#              #
#    Updated: 2025/01/24 00:12:15 by unbuntu          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN     = \033[0;32m
YELLOW    = \033[0;33m
BLUE      = \033[0;34m
RESET     = \033[0m
#===========================================================#
#						sources								#
#===========================================================#

SRC	=	main.c 
#mini_loop.c tokenization.c

#PREFIX_SOURCES = $(addprefix source/, $(SRC))

OBJS = $(SRC:.c=.o)

source/%.o:source/%.c
	@echo  "$(GREEN) [OK]       	$(YELLOW)Compaling ... $(BLUE)$<"
	@$(CCFLAG) -c $< -o $@

#===========================================================#
#															#
#===========================================================#

LIBFT = ../../libft/libft.a
LIBS = -lreadline

#===========================================================#
#															#
#===========================================================#

CCFLAG = cc -Wall -Wextra -Werror

RMF = rm -f

NAME = lexer_test

#===========================================================#
#															#
#===========================================================#

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ../../libft
	@echo  "$(GREEN) \n[OK]       	$(YELLOW)CREATED	loop test$(BLUE)**Test Loop**"
	@$(CCFLAG) -g3 $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	@make clean -C ../../libft
	@echo "$(RED) Delete	file obj P_S"
	$(RMF) $(OBJS)

fclean:
	@make fclean -C ../../libft
	@echo "$(RED) Delete	all	file obj P_S"
	@$(RMF) $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
