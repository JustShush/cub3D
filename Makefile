# - * - Makefile - * -

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I ./mlx_linux -fsanitize=address
RM = rm -rf

SRC_CUB	=	close.c init_player.c init.c input.c main.c minimap_put.c minimap.c render_anim.c render_calc.c render_draw.c render_utils.c render_utils2.c render.c textures.c utils.c
SRC_GNL =	gnl/gnl.c gnl/gnl_utils.c
SRC_MAP =	$(addprefix map/, check.c map_utils.c map_utils2.c map.c)

SRCS	=	$(addprefix $(SRC_DIR)/, $(SRC_CUB) $(SRC_MAP)) $(SRC_GNL)
OBJS	=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

GREEN	=	"\033[0;32m"
YELLOW	=	"\033[1;33m"
NC		=	"\033[0m"

SRC_DIR	=	src
OBJ_DIR	=	obj
LFT_DIR	=	libft

LIBFT	=	$(LFT_DIR)/libft.a
INC		=	-L ./mlx_linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LFT_DIR)
	@echo $(GREEN)"Compiled Libft!"$(NC)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INC) -o $(NAME)
	@echo $(GREEN)"Compiled!"$(NC)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	@$(CC) $(CFLAGS) -c $< -o $@

val: $(NAME)
	@valgrind --track-fds=yes --leak-check=full --track-origins=yes --show-leak-kinds=all ./cub3D

a: $(NAME)
	@./cub3D maps/neg_color.c

valtest: $(NAME)
	@for map_file in ./maps/*.cub; do \
		echo $(YELLOW)"$$map_file"$(NC); \
		valgrind --track-fds=yes --leak-check=full --track-origins=yes --show-leak-kinds=all ./cub3D $$map_file; \
	done

test: $(NAME)
	@for map_file in ./maps/*.cub; do \
		echo $(YELLOW)"$$map_file"$(NC); \
		./cub3D $$map_file; \
	done

clean:
		@$(RM) $(OBJS) $(OBJ_DIR)
		@make clean --no-print-directory -C $(LFT_DIR)

fclean: clean
		@$(RM) $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re val
