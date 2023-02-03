SRC = fdf.c
OBJ = $(SRC:.c=.o)
NAME = fdf
FLAGS = -Wall -Werror -Wextra -g
MAKE_LIBS = ./minilibx-linux/./configure
RM = rm -f
CC = cc

#Colors
GREEN=\033[0;32m
RED=\033[0;31m
END=\033[0m

all : $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(GREEN)---- Compiled ----$(END)"

clean :
	@$(RM) $(OBJ)
	@echo "$(RED)---- Cleaned ----$(END)"

fclean : clean 
	@$(RM) $(NAME)
	@echo "$(RED)---- All ----$(END)"

re : fclean all

.PHONY : all fclean clean re