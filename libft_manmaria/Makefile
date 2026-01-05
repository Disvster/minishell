SHELL := /bin/bash

# LIBFT
LIBFT_DIR = src/libft
LIBFTSRC =	ft_putendl_fd.c ft_isprint.c ft_strlcpy.c ft_atoi.c ft_lstclear_bonus.c \
		ft_strjoin.c ft_strrchr.c ft_isalpha.c ft_strlen.c ft_lstsize_bonus.c \
		ft_toupper.c ft_lstadd_back_bonus.c ft_strmapi.c ft_memcpy.c ft_lstdelone_bonus.c \
		ft_isdigit.c ft_putstr_fd.c ft_striteri.c ft_isalnum.c ft_memset.c \
		ft_itoa.c ft_split.c ft_calloc.c ft_strlcat.c ft_lstmap_bonus.c \
		ft_putnbr_fd.c ft_lstlast_bonus.c ft_memchr.c ft_strncmp.c \
		ft_lstadd_front_bonus.c ft_atol.c ft_atoi_base.c ft_abs.c ft_max.c\
		ft_bzero.c ft_memmove.c ft_substr.c ft_strtrim.c ft_lstnew_bonus.c \
		ft_strdup.c ft_lstiter_bonus.c ft_strchr.c ft_strchrnul.c ft_memcmp.c count_words.c \
		ft_strnstr.c ft_tolower.c ft_putchar_fd.c ft_isascii.c ft_swap.c
LIBFT_SRCS = $(addprefix $(LIBFT_DIR)/, $(LIBFTSRC))
LIBFT_OBJS = $(patsubst $(LIBFT_DIR)/%.c,$(OBJ_DIR)%.o,$(LIBFT_SRCS))

# GET NEXT LINE
GNL_DIR = src/gnl
GNLSRC = get_next_line_bonus.c get_next_line_utils_bonus.c
GNL_SRCS = $(addprefix $(GNL_DIR)/, $(GNLSRC))
GNL_OBJS = $(patsubst $(GNL_DIR)/%.c,$(OBJ_DIR)%.o,$(GNL_SRCS))

# FT_PRINTF
PRINTF_DIR = src/ft_printf
PRINTFSRC =	ft_printf.c ft_itoa_base.c ft_flags.c ft_itoa_pf.c ft_sub_cpy.c \
		ft_flags_helper2.c ft_see_format.c ft_indent.c ft_itoa_pt.c \
		ft_printf_utils2.c ft_flags_helper.c ft_printf_utils.c
PRINTF_SRCS = $(addprefix $(PRINTF_DIR)/, $(PRINTFSRC))
PRINTF_OBJS = $(patsubst $(PRINTF_DIR)/%.c,$(OBJ_DIR)%.o,$(PRINTF_SRCS))

# PROGRESS BAR
TOTAL_C := $(shell find src/ -type f -name '*.c' -not -path '*/.*' | wc -l)

define progress_bar
  @COUNT=$$(find obj -type f -name '*.o' | wc -l); \
  BAR_WIDTH=30; \
  NUM_HASHES=$$(( COUNT * BAR_WIDTH / $(TOTAL_C) )); \
  BAR=$$(printf "%-$${BAR_WIDTH}s" "$$(printf '%0.s#' $$(seq 1 $$NUM_HASHES))"); \
  echo -ne "Compiling: [$$BAR] ($$COUNT/$(TOTAL_C))\r"
endef

# CC = cc
CC = clang
CFLAGS = -Wall -Werror -Wextra -g -O3
OBJ_DIR = obj/
INC_DIR = incs/
NAME = libft.a
AR = ar rcs
RM = rm -f

all: $(OBJ_DIR) $(NAME)
	@echo -e "Compilation complete! libft.a file generated.             "

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)%.o: $(LIBFT_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	$(progress_bar)

$(OBJ_DIR)%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	$(progress_bar)

$(OBJ_DIR)%.o: $(PRINTF_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	$(progress_bar)

$(NAME): $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	@$(AR) $(NAME) $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)

clean: $(OBJ_DIR)
	@$(RM) $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	@echo "Cleaned .o files"
	@rmdir obj/

fclean: clean 
	@$(RM) $(NAME)
	@echo "Cleaned .a file"

re: fclean $(OBJ_DIR)
	@make --no-print-directory all

.PHONY: all clean fclean re
# $(LIBFTOBJ): $(LIBFTSRCS)
# 	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR)
#
# $(GNLOBJ): $(GNLSRCS)
# 	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR)
#
# $(PRINTFOBJ): $(PRINTFSRCS)
# 	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR)
# define oldprogress_bar
#   @COUNT=$$(find obj -type f -name '*.o' | wc -l); \
#   BAR=$$(printf "%-$$(($$COUNT*30/$(TOTAL_C)))s" | tr ' ' '#'); \
#   echo -ne "Compiling: [$$BAR] ($$COUNT/$(TOTAL_C))\r"
# endef
