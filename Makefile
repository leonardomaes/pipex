#Compile Options
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT = includes/libft/libft.a
PRINTF = includes/ft_printf/libftprintf.a

#
SRC =	main.c sources/utils.c sources/pipex.c
#

# Commands
RM = rm -rf
OBJ = $(SRC:.c=.o)

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
			$(RM) $(OBJ)
			@make --silent -C includes/ft_printf clean
			@make --silent -C includes/libft clean
fclean: clean
			$(RM) $(NAME)
			@make --silent -C includes/ft_printf fclean
			@make --silent -C includes/libft  fclean

re: fclean all
