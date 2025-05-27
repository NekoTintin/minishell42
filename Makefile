# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 18:38:59 by bchallat          #+#    #+#              #
#    Updated: 2025/03/05 19:45:33 by benoitchallat    ###   ########.fr        #
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

CCFLAG = cc -Wall -Wextra -Werror -g3 -I includes/ -fsanitize=address
RMF = rm -rf
NAME = minishell_test

#===========================================================#
#						sources								#
#===========================================================#

SRC	=	minishell.c \
		testeur/lib_test_lexer.c \
		testeur/lib_test_parsing.c\
		lexer/chain_list.c \
		lexer/lexer.c \
		lexer/lexer_utils.c \
		lexer/tokenization.c \
		parsing/parser.c \
		parsing/parse_valid_lexer.c\
		parsing/parse_conc_quote.c\
		parsing/make_element_struct.c\
		parsing/free_element_struct.c \
		parsing/parse_ast_utils.c \
		parsing/parse_ast_redir_utils.c \
		parsing/parse_ast_redirect.c \
		parsing/parse_ast.c \

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
	@echo  "$(GREEN)[OK]       	✅ $(YELLOW)CREATED	loop test$(BLUE)	**Test Loop**\n"
	@$(CCFLAG) -g3 $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	@make clean -C libft/ > /dev/null
	@echo "$(RED)🧹 Delete	file obj P_S"
	@$(RMF) $(OBJDIR) $(OBJS)

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
	@echo "${GREEN}[->]${YELLOW}		📂 Creating directory ${OBJ_DIR}...$(BLUE)	(object)$(RESET)\n"
	@mkdir -p ${OBJDIR}
	@mkdir -p ${OBJDIR}/lexer
	@mkdir -p ${OBJDIR}/parsing
	@mkdir -p ${OBJDIR}/signal
	@mkdir -p ${OBJDIR}/testeur
	@mkdir -p ${OBJDIR}/util
	@mkdir -p ${OBJDIR}/execution
	@mkdir -p ${OBJDIR}/execution/builtin
