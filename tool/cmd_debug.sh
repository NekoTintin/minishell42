#!/bin/bash

norminette
make && make clean
valgrind --suppressions=tool/readline.supp --trace-children=no --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell
make fclean
