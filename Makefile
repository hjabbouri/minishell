SRC_C = src/main.c \
	src/builtins/blt_cd.c \
	src/builtins/blt_echo.c \
	src/builtins/blt_env.c \
	src/builtins/blt_exit.c \
	src/builtins/blt_export_utils.c \
	src/builtins/blt_export.c \
	src/builtins/blt_pwd.c \
	src/builtins/blt_unset.c \
	src/builtins/blt_utils.c \
	src/env/env_utils.c \
	src/env/env.c \
	src/env/getters.c \
	src/lexer/lexer.c \
	src/lexer/word.c \
	src/libft/ft_atoi.c \
	src/libft/ft_chr.c \
	src/libft/ft_isalnum.c \
	src/libft/ft_isalpha.c \
	src/libft/ft_isdigit.c \
	src/libft/ft_itoa.c \
	src/libft/ft_malloc.c \
	src/libft/ft_ptrtoa.c \
	src/libft/ft_strchr.c \
	src/libft/ft_strcpy.c \
	src/libft/ft_strdup.c \
	src/libft/ft_strjoin.c \
	src/libft/ft_strlcpy.c \
	src/libft/ft_strlen.c \
	src/libft/ft_strncmp.c \
	src/libft/ft_strndup.c \
	src/libft/ft_substr.c \
	src/llnode/list_create.c \
	src/llnode/list_destroy.c \
	src/llnode/list.c \
	src/reducer/heredoc.c \
	src/reducer/pipe.c \
	src/reducer/smp.c \
	src/reducer/signals.c

SRC_O = $(SRC_C:.c=.o)
CC = cc
CXXFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
NAME = minishell

ifeq ($(shell uname), Darwin)
	READLINE = $(shell brew --prefix readline)
	export CPATH += :$(READLINE)/include
	export LIBRARY_PATH += :$(READLINE)/lib
endif

all: $(NAME)
$(NAME): $(SRC_O) src/include.h
	$(CC) $(CXXFLAGS) $(SRC_O) $(LDFLAGS) -o $(NAME)
%.o : %.c
	$(CC) $(CXXFLAGS) $(INC) -o $@ -c $<
re: fclean all
clean:
	rm -rf $(SRC_O) $(SRC_C:.c=.d)
fclean: clean
	rm -rf $(NAME)

-include $(SRC_C:.c=.d)
.PHONY: all re bonus rebonus clean fclean