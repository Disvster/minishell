SRCS = count_words.c ft_atoi.c ft_strjoin.c ft_strdup.c ft_putendl_fd.c ft_isalpha.c ft_strnstr.c ft_itoa.c ft_putchar_fd.c ft_isdigit.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalnum.c ft_isascii.c ft_strchr.c ft_strmapi.c ft_calloc.c ft_putstr_fd.c ft_putnbr_fd.c ft_toupper.c ft_strtrim.c ft_memcpy.c ft_split.c ft_isprint.c ft_memset.c ft_substr.c ft_strncmp.c ft_strrchr.c ft_strlcat.c ft_memmove.c ft_striteri.c ft_bzero.c ft_tolower.c ft_strlcpy.c 
OBJS = $(SRCS:.c=.o)
BSRCS = ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstadd_back_bonus.c 
BOBJS = $(BSRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra -c
NAME = libft.a
ARRCS = ar rcs
ARRS = ar rs
RM = rm -f

.c.o:
	$(CC) $(CFLAGS) $<

$(NAME): $(OBJS)
	$(ARRCS) $(NAME) $(OBJS)

$(BOBJS): $(BSRCS)
	$(CC) $(CFLAGS) $(BSRCS)

bonus: $(NAME) $(BOBJS)
	$(ARRS) $(NAME) $(BOBJS)

all: $(NAME)
	
clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re
