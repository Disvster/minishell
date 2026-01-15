CC = clang
CFLAGS = -Wall -Wextra -Werror -Iincs/
LDFLAGS = -Lvendor/readline/lib -lreadline
LIBFT = libft_manmaria/libft.a
LIBFT_DIR = libft_manmaria/
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o
	@make --no-print-directory -C $(LIBFT_DIR) clean

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean
	@make --no-print-directory all

PHONY: clean fclean re all
