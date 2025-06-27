# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 18:38:59 by bchallat          #+#    #+#              #
#    Updated: 2025/06/25 12:51:03 by qupollet         ###   ########.fr        #
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
NAME = minishell

#===========================================================#
#						sources								#
#===========================================================#

SRC	=	minishell.c \
		utils/signal.c \
		utils/env_in_lexer.c \
		utils/tenv_varenv.c \
		utils/minishell_utils.c \
		env/env_func.c \
		env/env_utils.c \
		env/env_init.c \
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
		execution/builtin/mini_cd.c \
		execution/builtin/mini_echo.c \
		execution/builtin/mini_env.c \
		execution/builtin/mini_exit.c \
		execution/builtin/mini_export.c \
		execution/builtin/mini_pwd.c \
		execution/builtin/mini_unset.c \
		execution/builtins.c \
		execution/exec_init.c \
		execution/exec_one.c \
		execution/exec_utils.c \
		execution/exec.c \
		execution/file_management.c \
		execution/find_in_path.c \
		execution/pipeline.c \
		execution/redirect_heredoc.c \
		execution/redirect.c \
		execution/redirect_utils.c \
		execution/utils.c \

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
	@echo  "$(GREEN)[OK]       	✅ $(YELLOW)CREATED	.exe ... $(BLUE)Minishell\n$(RESET)"
	@$(CCFLAG) -g3 $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	@make clean -C libft/ > /dev/null
	@echo "$(RED)🧹 Delete	file obj P_S"
	@$(RMF) $(OBJDIR) $(OBJS)

fclean:
	@make fclean -C libft/ > /dev/null
	@echo "$(RED)🧹 Delete	all	file obj P_S"
	@$(RMF) $(OBJDIR) $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re

#===========================================================#
#						other/rules							#
#===========================================================#

${OBJDIR}:
	@echo "${GREEN}[->]${YELLOW}		📂 Creating directory ${OBJ_DIR}...$(BLUE)	(object)$(RESET)\n"
	@mkdir -p ${OBJDIR}
	@mkdir -p ${OBJDIR}/env
	@mkdir -p ${OBJDIR}/lexer
	@mkdir -p ${OBJDIR}/parsing
	@mkdir -p ${OBJDIR}/signal
	@mkdir -p ${OBJDIR}/testeur
	@mkdir -p ${OBJDIR}/utils
	@mkdir -p ${OBJDIR}/execution
	@mkdir -p ${OBJDIR}/execution/builtin
	@mkdir -p ${OBJDIR}/env
