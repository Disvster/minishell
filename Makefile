CC = clang -g
CFLAGS = -Wall -Wextra -Werror -Iincs/
LDFLAGS = -Lvendor/readline/lib -lreadline
LIBFT = libft_manmaria/libft.a
LIBFT_DIR = libft_manmaria/
SRC_DIRS = src \
		   src/env_list \
		   src/executor \
		   src/executor/builtin \
		   src/executor/command_list \
		   src/expansion \
		   src/ft_printf_fd \
		   src/heredoc \
		   src/lexing \
		   src/parsing \
		   src/signal \
		   src/token_list_utils

VPATH = $(SRC_DIRS)
OBJ_DIR = obj

#TODO: change wildcard, can't use them
SRCS = $(foreach d,$(SRC_DIRS),$(wildcard $(d)/*.c))
OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRCS:.c=.o)))
NAME = minishell

# PROGRESS BAR
TOTAL_C := $(shell find src/ -type f -name '*.c' -not -path '*/.*' | wc -l)

define	progress_bar
	@COUNT=$$(find obj -type f -name '*.o' | wc -l); \
	BAR_WIDTH=30; \
	NUM_HASHES=$$(( COUNT * BAR_WIDTH / $(TOTAL_C) )); \
	BAR=$$(printf "%-$${BAR_WIDTH}s" "$$(printf '%0.s#' $$(seq 1 $$NUM_HASHES))"); \
	echo -ne "Compiling: [$$BAR] ($$COUNT/$(TOTAL_C))\r"
endef

all: $(OBJ_DIR) $(LIBFT) $(NAME)
	@echo -e "Compilation complete! minishell file generated.                         \n"

print_minishell:
	@echo -e "\n======  MINISHELL ======"

print_libft:
	@echo -e "\n=====  Libft  ====="

$(OBJ_DIR):
	@mkdir $@

$(LIBFT):print_libft
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): print_minishell $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(progress_bar)

clean: $(OBJ_DIR)
	@make --no-print-directory print_libft
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@make --no-print-directory print_minishell
	@rm -f $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	@echo -e "cleaned .o files\n"

fclean: $(OBJ_DIR)
	@make --no-print-directory print_libft
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@make --no-print-directory print_minishell
	@$(RM) -r $(OBJ_DIR)
	@echo "Cleaned .o files"
	@$(RM) $(NAME)
	@echo -e "Cleaned minishell executable\n"

re: fclean $(OBJ_DIR)
	@make --no-print-directory all

PHONY: clean fclean re all print_libft print_minishell
