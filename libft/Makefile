# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 10:29:40 by qupollet          #+#    #+#              #
#    Updated: 2025/01/20 17:02:55 by qupollet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ_DIR = objs

HEADER = libft.h

SRC =		ft_atoi.c \
			ft_itoa.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_memchr.c \
			ft_memcpy.c \
			ft_memset.c \
			ft_memmove.c \
			ft_memcmp.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putstr_fd.c \
			ft_putnbr_fd.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_split.c \
			ft_strtrim.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strmapi.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			get_next_line.c \
			ft_utils.c \
			ft_printf.c \
			ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstlast_bonus.c

SRCS = ${SRC}
OBJECTS = ${addprefix ${OBJ_DIR}/, ${SRCS:.c=.o}}

CC = @cc
CFLAGS = -Wall -Wextra -Werror

# Colours
RED = \033[0;91m
GREEN = \033[0;33m
BLUE = \033[1;34m
YELLOW = \033[1;33m
NC = \033[0m 

all: ${NAME}
	@echo "${GREEN}✅ LIBFT compiled !"

# Compilation de l'exécutable
${NAME}: ${OBJECTS}
	@ar -rcs ${NAME} ${OBJECTS}

# Règle pour compiler les fichiers objets dans le dossier objs
${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
	@echo "${BLUE}━  🛠️  Compiling $< into $@...${NC}"
	${CC} ${CFLAGS} -c $< -o $@

# Création du répertoire objs si non existant
${OBJ_DIR}:
	@echo "${YELLOW}📂 Creating directory ${OBJ_DIR}...${NC}"
	@mkdir -p ${OBJ_DIR}

# Nettoyage des fichiers objets
clean:
	@echo "${RED}🧹 Cleaning object directory...${NC}"
	@rm -rf ${OBJ_DIR}

# Nettoyage complet
fclean: clean
	@echo "${RED}🧹 Cleaning executable...${NC}"
	@rm -f ${NAME}

# Rebuild complet
re: fclean all

.PHONY: all clean fclean re
