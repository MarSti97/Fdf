SRC = fdf.c list_funcs.c map.c rotate.c third_dim.c math.c controls.c controls_util.c \
colour.c colour_utils.c tools.c
OBJ = $(SRC:.c=.o)
NAME = fdf
FLAGS = -Wall -Werror -Wextra -g 
LIBFT = make -C ./libft --no-print-directory
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
# @$(LIBFT)
	@$(CC) -fsanitize=address $(OBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -g -o $(NAME)
	@echo "$(GREEN)>>>> Compiled <<<<$(END)"

clean :
	@$(RM) $(OBJ)
# @make clean -C ./libft --no-print-directory
	@echo "$(RED)>>>> Cleaned <<<<$(END)"

fclean : clean 
	@$(RM) $(NAME)
# @make fclean -C ./libft --no-print-directory
	@echo "$(RED)>>>> All <<<<$(END)"

re : fclean all

.PHONY : all fclean clean re make