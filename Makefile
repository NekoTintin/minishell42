# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 18:38:59 by bchallat          #+#    #+#              #
#    Updated: 2025/02/24 16:38:57 by bchallat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===========================================================#
#							var								#
#===========================================================#

GREEN     = \033[0;32m
YELLOW    = \033[0;33m
BLUE      = \033[0;34m
RESET     = \033[0m

SRCDIR = src
OBJDIR = object

LIBFT = libft/libft.a
LIBS = -lreadline

CCFLAG = cc -Wall -Wextra -Werror -g3 -I includes/
RMF = rm -rf
NAME = minishell_test

#===========================================================#
#						sources								#
#===========================================================#

SRC	=	testeur/main.c \
		testeur/lib_test.c \
		lexer/chain_list.c \
		lexer/lexer.c \
		lexer/lexer_utils.c \
		lexer/tokenization.c \
		parsing/ps_clean_lexer.c \
		

SRCS = ${addprefix ${SRCDIR}/, ${SRC}}
OBJS = ${addprefix ${OBJDIR}/, $(SRC:.c=.o)}

object/%.o:src/%.c | $(OBJDIR)
	@echo  "$(GREEN)[OK]       	🛠️ $(YELLOW)Compaling ... $(BLUE)$<"
	@$(CCFLAG) -c $< -o $@

#===========================================================#
#							rules							#
#===========================================================#

all: $(NAME)

$(NAME): $(OBJS)
	@echo  "$(GREEN)[..]       	🛠️ $(YELLOW)MAKE	libft ...$(BLUE)libft/libft.a\n"
	@make -C libft/ > /dev/null
	@echo  "$(GREEN)[OK]       	✅ $(YELLOW)CREATED	loop test$(BLUE)**Test Loop**\n"
	@$(CCFLAG) -g3 $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	@make clean -C libft/ > /dev/null
	@echo "$(RED)🧹 Delete	file obj P_S"
	$(RMF) $(OBJDIR) $(OBJS)

fclean:
	@make fclean -C libft/ > /dev/null
	@echo "$(RED)🧹 Delete	all	file obj P_S"
	@$(RMF) $(OBJDIR) $(OBJS) $(NAME)

re: all

.PHONY: all clean fclean re

#===========================================================#
#						other/rules							#
#===========================================================#

${OBJDIR}:
	@echo "${YELLOW}📂 Creating directory ${OBJ_DIR}...$(BLUE)		object/$(RESET)"
	@mkdir -p ${OBJDIR}
	@mkdir -p ${OBJDIR}/builtin
	@mkdir -p ${OBJDIR}/lexer
	@mkdir -p ${OBJDIR}/parsing
	@mkdir -p ${OBJDIR}/signal
	@mkdir -p ${OBJDIR}/testeur
	@mkdir -p ${OBJDIR}/util