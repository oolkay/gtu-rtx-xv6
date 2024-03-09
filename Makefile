NAME := cub3d
B_NAME := cub3d_bonus

CC := gcc

CFLAGS := 
SOMEFLAG = -lft -lmlx -lm -lX11 -lXext

RM := rm -f

SRCS_DIR := srcs/
SRCS := ./srcs/calc_utils.c \
		./srcs/checks.c \
		./srcs/ft_assign_texture.c \
		./srcs/ft_draw_wall.c \
		./srcs/ft_exit_and_free.c \
		./srcs/ft_fill_textures.c \
		./srcs/ft_import_map.c \
		./srcs/ft_init_images.c \
		./srcs/ft_move_player.c \
		./srcs/ft_parse_map_closed.c \
		./srcs/ft_parse_map.c \
		./srcs/ft_render.c \
		./srcs/ft_start_game.c \
		./srcs/ft_update.c \
		./srcs/ft_wall_dimension.c \
		./srcs/gnl_utils.c \
		./srcs/gnl.c \
		./srcs/list_utils.c \
		./srcs/main.c \
		./srcs/matrix.c

OBJS_DIR := objs/
OBJS := ./objs/calc_utils.o \
		./objs/checks.o \
		./objs/ft_assign_texture.o \
		./objs/ft_draw_wall.o \
		./objs/ft_exit_and_free.o \
		./objs/ft_fill_textures.o \
		./objs/ft_import_map.o \
		./objs/ft_init_images.o \
		./objs/ft_move_player.o \
		./objs/ft_parse_map_closed.o \
		./objs/ft_parse_map.o \
		./objs/ft_render.o \
		./objs/ft_start_game.o \
		./objs/ft_update.o \
		./objs/ft_wall_dimension.o \
		./objs/gnl_utils.o \
		./objs/gnl.o \
		./objs/list_utils.o \
		./objs/main.o \
		./objs/matrix.o

BONUS_DIR := bonus/
BONUS_SRCS := ./bonus/calc_utils.c \
		./bonus/checks.c \
		./bonus/ft_assign_texture.c \
		./bonus/ft_draw_wall.c \
		./bonus/ft_exit_and_free.c \
		./bonus/ft_fill_textures.c \
		./bonus/ft_import_map.c \
		./bonus/ft_init_images.c \
		./bonus/ft_move_player.c \
		./bonus/ft_parse_map_closed.c \
		./bonus/ft_parse_map.c \
		./bonus/ft_render.c \
		./bonus/ft_start_game.c \
		./bonus/ft_update.c \
		./bonus/gnl_utils.c \
		./bonus/gnl.c \
		./bonus/main.c \
		./bonus/matrix.c

BONUS_OBJS_DIR := bonus_obj/
BONUS_OBJS := ./bonus_obj/calc_utils.o \
		./bonus_obj/checks.o \
		./bonus_obj/ft_assign_texture.o \
		./bonus_obj/ft_draw_wall.o \
		./bonus_obj/ft_exit_and_free.o \
		./bonus_obj/ft_fill_textures.o \
		./bonus_obj/ft_import_map.o \
		./bonus_obj/ft_init_images.o \
		./bonus_obj/ft_move_player.o \
		./bonus_obj/ft_parse_map_closed.o \
		./bonus_obj/ft_parse_map.o \
		./bonus_obj/ft_render.o \
		./bonus_obj/ft_start_game.o \
		./bonus_obj/ft_update.o \
		./bonus_obj/gnl_utils.o \
		./bonus_obj/gnl.o \
		./bonus_obj/main.o \
		./bonus_obj/matrix.o

LIBFT_DIR := libft
MINILIBX_DIR := minilibx

all: $(NAME)
bonus : $(B_NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC)   $(CFLAGS) -I$(LIBFT_DIR) -L$(LIBFT_DIR)  $(OBJS) $(SOMEFLAG) -o $(NAME)
	@rm -rf $(B_NAME)
	@echo "Compiled cub3d"

$(B_NAME): $(BONUS_OBJS_DIR) $(BONUS_OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC)  $(CFLAGS) -I$(LIBFT_DIR) -L$(LIBFT_DIR)  $(BONUS_OBJS) $(SOMEFLAG) -o $(B_NAME)
	@rm -rf $(NAME)
	@echo "Compiled cub3d_bonus"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) ${SOMEFLAG} -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(BONUS_OBJS_DIR)%.o: $(BONUS_DIR)%.c
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -c $< -o $@

$(BONUS_OBJS_DIR):
	@mkdir -p $(BONUS_OBJS_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MINILIBX_DIR)
	@$(RM) -r $(OBJS_DIR)
	@$(RM) -r $(BONUS_OBJS_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@$(RM) $(B_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
