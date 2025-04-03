# Nom du projet
NAME = minishell

SRCS_DIR = srcs

# List of source files
SRCS = $(SRCS_DIR)/minishell_main.c \
		$(SRCS_DIR)/1_env.c \
		$(SRCS_DIR)/2_tokenization.c \
		$(SRCS_DIR)/3_parsing.c \
		$(SRCS_DIR)/utils.c \
		$(SRCS_DIR)/free.c \
		execution/path.c \
		execution/exec.c \
		execution/redirections.c \
		execution/utils_exec.c \
		utils000.c \
		builtins/builtins.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		builtins/cd.c \
		signal/signal.c \

# Compilateur
CC = cc

# Flags
CFLAGS = -Wall -Wextra -Werror -g

# Flags pour readline
LDFLAGS = -lreadline -lhistory

# Fichiers objets générés
OBJS = $(SRCS:.c=.o)

# Répertoires des bibliothèques
LIBFT_DIR = ./libft_custom

# Fichiers des bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a

# Couleurs pour afficher les messages
RED = \033[31m
GREEN = \033[32m
CYAN = \033[36m
RESET = \033[0m

# Règle par défaut pour créer le programme final
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Compilation du projet...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(LDFLAGS)

# Règle pour compiler la Libft
$(LIBFT):
	@echo "$(GREEN)Compilation de la Libft...$(RESET)"
	$(MAKE) -C $(LIBFT_DIR)

# Règle générique pour compiler les fichiers .c en .o
%.o: %.c
	@echo "$(GREEN)Compilation de $<...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@ -I .

# Règle par défaut pour compiler le programme
all: $(NAME)

# Nettoyage des fichiers objets
clean:
	@echo "$(RED)Nettoyage des objets...$(RESET)"
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

# Nettoyage complet (objets + programme)
fclean: clean
	@echo "$(RED)Nettoyage complet...$(RESET)"
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

# Règle pour tout refaire (nettoyage complet + recompilation)
re: fclean all

# Déclaration des cibles sans fichiers associés
.PHONY: all clean fclean re