CC = gcc
FLAGS = -Wall -Wextra -Werror

NAME = pipex

BONUS_NAME = pipex_bonus

LIBFT_DIR = libft/

SRC_DIR = src/

MD_OBJ_DIR = obj_pp/
BO_OBJ_DIR = obj_bo/

BONUS_DIR = pipex_bonus/

INC_DIR = includes/

LIBFT = $(LIBFT_DIR)libft.a

SOURCES = check_cmd.c \
	child.c \
	exit.c \
	init.c \
	pipex.c \
	run.c \
	utils.c


BONUS_SOURCES = check_cmd_bonus.c \
	child_bonus.c \
	exit_bonus.c \
	here_doc_bonus.c \
	init_bonus.c \
	pipex_bonus.c \
	run_bonus.c \
	utils_bonus.c

BONUS_SRC_DIR = $(addprefix $(SRC_DIR), $(BONUS_DIR))

OBJ = $(SOURCES:.c=.o)
BONUS_OBJ = $(BONUS_SOURCES:.c=.o)

OBJS = $(addprefix $(MD_OBJ_DIR), $(OBJ))
BONUS_OBJS = $(addprefix $(BO_OBJ_DIR), $(BONUS_OBJ))

all: $(NAME) $(BONUS_NAME)

bonus: $(BONUS_NAME)

$(MD_OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIBFT_DIR)

$(BO_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR) -I $(LIBFT_DIR)

$(NAME): $(MD_OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -o  $@ $(OBJS) $(LIBFT)

$(BONUS_NAME): $(BO_OBJ_DIR) $(LIBFT) $(BONUS_OBJS)
	$(CC) $(FLAGS) -o $@  $(BONUS_OBJS) $(LIBFT)

$(MD_OBJ_DIR):
	mkdir  $(MD_OBJ_DIR)

$(BO_OBJ_DIR):
	mkdir $(BO_OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean: miniclean
	make -C $(LIBFT_DIR) clean

miniclean:
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)
	rm -fd $(MD_OBJ_DIR)
	rm -fd $(BO_OBJ_DIR)

fclean: miniclean 
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

minifclean: miniclean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

minire : minifclean all

.PHONY: all bonus clean fclean miniclean minifclean re minire
