# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 10:29:40 by qupollet          #+#    #+#              #
#    Updated: 2025/01/21 21:35:42 by qupollet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
INCLUDE_DIR = includes
OBJ_DIR = objs

LIBFT_DIR = libft

SRC =	minishell.c \
		builtin/pwd.c \

SRCS = ${addprefix ${SRC_DIR}/, ${SRC}}
OBJECTS = ${addprefix ${OBJ_DIR}/, ${SRC:.c=.o}}
LIBFT = ${LIBFT_DIR}/libft.a

CC = @cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline -lhistory -lc

# Colours
RED = \033[0;91m
GREEN = \033[0;33m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[0m 

all: ${NAME}
	@echo "${GREEN}✅ minishell compiled !"

# Compile the libft
${LIBFT}:
	@echo "${BLUE}🛠️  Compiling LIBFT ${NC}"
	@make --no-print-directory -C ${LIBFT_DIR}

# Compile the main executable
${NAME}: ${LIBFT} ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} ${LIBFT} -o ${NAME} ${LDFLAGS}

# Rule to compile obj files
${OBJ_DIR}/%.o: ${SRC_DIR}/%.c | ${OBJ_DIR}
	@echo "${BLUE}━  🛠️  Compiling $< into $@...${NC}"
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -I ${LIBFT_DIR} -c $< -o $@

# Don't forget to add folder here if folder are added in src directory
# Create an obj directory if it doesn't exist
${OBJ_DIR}:
	@echo "${YELLOW}📂 Creating directory ${OBJ_DIR}...${NC}"
	@mkdir -p ${OBJ_DIR}
	@mkdir -p ${OBJ_DIR}/builtin

# Cleaning obj files and remove obj directory
clean:
	@echo "${RED}🧹 Cleaning minishell object directory...${NC}"
	@rm -rf ${OBJ_DIR}
	@rm -rf ${OBJ_DIR}/builtin
	@make clean --no-print-directory -C ${LIBFT_DIR} 

# Clean all
fclean: clean
	@echo "${RED}🧹 Cleaning minishell...${NC}"
	@rm -f ${NAME}
	@make fclean --no-print-directory -C ${LIBFT_DIR} 

# Recompile
re: fclean all

.PHONY: all clean fclean re
