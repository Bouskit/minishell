PART = base/ft_atoi.c \
	base/ft_bzero.c \
	base/ft_calloc.c \
	base/ft_isalnum.c \
	base/ft_isalpha.c \
	base/ft_isascii.c \
	base/ft_isdigit.c \
	base/ft_isprint.c \
	base/ft_memchr.c \
	base/ft_memcmp.c \
	base/ft_memcpy.c \
	base/ft_memmove.c \
	base/ft_memset.c \
	base/ft_strchr.c \
	base/ft_strdup.c \
	base/ft_strlcat.c \
	base/ft_strlcpy.c \
	base/ft_strlen.c \
	base/ft_strncmp.c \
	base/ft_strnstr.c \
	base/ft_strrchr.c \
	base/ft_tolower.c \
	base/ft_toupper.c \
	base/ft_strcpy.c

ADDITIONAL = base/ft_itoa.c \
		base/ft_putchar_fd.c \
		base/ft_putendl_fd.c \
		base/ft_putnbr_fd.c \
		base/ft_putstr_fd.c \
		base/ft_split.c \
		base/ft_strjoin.c \
		base/ft_strmapi.c \
		base/ft_strtrim.c \
		base/ft_substr.c \
		base/ft_striteri.c \
		base/ft_strcmp.c \
		base/ft_strcat.c \

BONUS = base/ft_lstadd_back_bonus.c \
		base/ft_lstadd_front_bonus.c \
		base/ft_lstclear_bonus.c \
		base/ft_lstdelone_bonus.c \
		base/ft_lstiter_bonus.c \
		base/ft_lstlast_bonus.c \
		base/ft_lstmap_bonus.c \
		base/ft_lstnew_bonus.c \
		base/ft_lstsize_bonus.c \

PRINTF = printf/ft_printf.c \
		printf/ft_putchar_len.c \
		printf/ft_putstr_len.c \
		printf/ft_putnbr_len.c \
		printf/ft_uputnbr_len.c \
		printf/ft_hexa_len.c \
		printf/ft_adresse.c \

GNL = gnl/get_next_line.c\
	gnl/get_next_line_utils.c\

SRCS = $(PART) $(ADDITIONAL) $(BONUS) $(PRINTF) $(GNL)

SRCSALL = $(PART) $(ADDITIONAL) $(BONUS) $(PRINTF) $(GNL)

OBJS = $(SRCS:.c=.o)

OBJSALL = $(SRCSALL:.c=.o)

NAME = libft.a

LIBC = ar rc

LIBR = ranlib

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

all : $(NAME)

$(NAME) : $(OBJS)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBR) $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I .
	
bonus :	$(OBJSALL)
	$(LIBC) $(NAME) $(OBJSALL)
	$(LIBR) $(NAME)

clean :
	rm -f $(OBJSALL) 

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus


