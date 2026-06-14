SHELL :=/bin/bash

CC := clang -g
CFLAGS := -Wall -Wextra -Werror -Iincs/
LDFLAGS := -Lvendor/readline/lib -lreadline
LIBFT := libft_manmaria/libft.a
LIBFT_DIR := libft_manmaria/
SRC_DIRS := src

OBJ_DIR := obj/
SRCS := \
	$(SRC_DIRS)/env_list/env_list_utils.c \
	$(SRC_DIRS)/env_list/init_env.c \
	$(SRC_DIRS)/executor/builtin/cd.c \
	$(SRC_DIRS)/executor/builtin/echo.c \
	$(SRC_DIRS)/executor/builtin/env.c \
	$(SRC_DIRS)/executor/builtin/pwd.c \
	$(SRC_DIRS)/executor/builtin/exit.c \
	$(SRC_DIRS)/executor/builtin/export.c \
	$(SRC_DIRS)/executor/builtin/export_helpers.c \
	$(SRC_DIRS)/executor/builtin/export_utils.c \
	$(SRC_DIRS)/executor/builtin/unset.c \
	$(SRC_DIRS)/executor/command_list/cmdlist_helpers.c \
	$(SRC_DIRS)/executor/command_list/cmdlist.c \
	$(SRC_DIRS)/executor/command_list/cmdlist_utils.c \
	$(SRC_DIRS)/executor/command_list/cmdlist_utils2.c \
	$(SRC_DIRS)/executor/executor.c \
	$(SRC_DIRS)/executor/executor_helpers.c \
	$(SRC_DIRS)/executor/executor_utils.c \
	$(SRC_DIRS)/expansion/expansion.c \
	$(SRC_DIRS)/expansion/expansion_utils.c \
	$(SRC_DIRS)/ft_printf_fd/ft_printf_fd.c \
	$(SRC_DIRS)/ft_printf_fd/ft_puthexa_fd.c \
	$(SRC_DIRS)/ft_printf_fd/ft_putptr_fd.c \
	$(SRC_DIRS)/ft_printf_fd/ft_putunsnbr_fd.c \
	$(SRC_DIRS)/heredoc/heredoc.c \
	$(SRC_DIRS)/heredoc/heredoc_utils.c \
	$(SRC_DIRS)/lexing/lex_utils.c \
	$(SRC_DIRS)/lexing/lex_utils2.c \
	$(SRC_DIRS)/lexing/lexer.c \
	$(SRC_DIRS)/parsing/syntax_check.c \
	$(SRC_DIRS)/parsing/parsing.c \
	$(SRC_DIRS)/parsing/parsing_utils.c \
	$(SRC_DIRS)/redirect/redirect.c \
	$(SRC_DIRS)/redirect/redirect_utils.c \
	$(SRC_DIRS)/signal/signal_block.c \
	$(SRC_DIRS)/signal/signal.c \
	$(SRC_DIRS)/token_list_utils/list_utils2.c \
	$(SRC_DIRS)/token_list_utils/list_utils.c \
	$(SRC_DIRS)/shell_utils/clear.c \
	$(SRC_DIRS)/shell_utils/prompt.c \
	$(SRC_DIRS)/shell_utils/save_restore.c \
	$(SRC_DIRS)/main.c

OBJS := $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
NAME := minishell
RM := rm -f

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
	@mkdir -p $@

$(LIBFT): print_libft
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): print_minishell $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	$(progress_bar)

clean: $(OBJ_DIR)
	@make --no-print-directory print_libft
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@make --no-print-directory print_minishell
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

.PHONY: clean fclean re all print_libft print_minishell
