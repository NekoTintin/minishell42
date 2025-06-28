#!/bin/bash

make && make clean
valgrind --suppressions=tool/readline.supp --leak-check=full --show-leak-kinds=all ./minishell
make fclean
