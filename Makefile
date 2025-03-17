NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I include/ -I libft/
LIBS = -lreadline -lncurses

SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# List of source files
SRCS = $(SRCS_DIR)/minishell_main.c \
		$(SRCS_DIR)/1_env.c \
		$(SRCS_DIR)/2_tokenization.c \
		$(SRCS_DIR)/3_parsing.c \
		$(SRCS_DIR)/utils.c \
		$(SRCS_DIR)/free.c

# Convert source files to object files
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Default target
all: $(NAME)

# Compile the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile minishell with libft
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCLUDE) -L$(LIBFT_DIR) -lft $(LIBS)

# Rule to compile object files
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure objs/ directory exists
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
