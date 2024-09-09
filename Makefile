#Compile Options
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT = includes/libft/libft.a
PRINTF = includes/ft_printf/libftprintf.a

#
SRC =	sources/main.c sources/utils.c sources/pipex.c
SRC_BONUS = bonus/main_bonus.c bonus/pipex_bonus.c bonus/utils_bonus.c
#

# Commands
RM = rm -rf
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(SRC_BONUS:.c=.o)
all: $(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c $*.c -o $*.o

$(LIBFT):
			@make --silent -C includes/libft

$(PRINTF):
			@make --silent -C includes/ft_printf

$(NAME) : $(OBJ) $(PRINTF) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF)

clean:
			$(RM) $(OBJ) $(BONUS_OBJ)
			@make --silent -C includes/ft_printf clean
			@make --silent -C includes/libft clean
fclean: clean
			$(RM) $(NAME)
			@make --silent -C includes/ft_printf fclean
			@make --silent -C includes/libft  fclean

re: fclean all

bonus : clean $(BONUS_OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJ) $(LIBFT)
