# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/18 20:55:16 by itan              #+#    #+#              #
#    Updated: 2023/03/28 02:26:42 by itan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRC_DIR	= src
OBJ_DIR	= obj

# this is for mirroring the out dir
OBJ_DIRS= $(subst $(SRC_DIR), $(OBJ_DIR), $(shell find $(SRC_DIR) -type d))

SRC		= $(shell find $(SRC_DIR) -name '*.c')
OBJ		= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

AR		= ar -rcs
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
RM		= rm -f
INC		= $(addprefix -I , $(shell find includes -type d -name includes))

LIBDIR	= includes/libft
LIB		= -L$(LIBDIR) -lft -lreadline
LIBNAME	= libft.a
# this is for debugging
DNAME	= d.out
DDIR	= test
DFLAGS	= -fsanitize=address -fdiagnostics-color=always -g3
DSRC	= $(shell find $(DDIR) -name '*.c')
DOBJ	= $(DSRC:.c=.o)

# ** COLORS ** #
BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
WHITE		= \033[37m
B_BLACK		= \033[40m
B_RED		= \033[41m
B_GREEN		= \033[42m
B_YELLOW	= \033[43m
B_BLUE		= \033[44m
B_MAGENTA	= \033[45m
B_CYAN		= \033[46m
B_WHITE		= \033[47m
BRIGHT		= \033[1m
NORMAL		= \033[0m
BLINK		= \033[4m
REVERSE		= \033[5m
UNDERLINE	= \033[3m

CLR_TERM	= \033[H\033[2J

all::
		@printf "$(CLR_TERM)$(WHITE)$(BRIGHT) __________________________________ $(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT)< Trying my best to make $(CYAN)$(NAME)$(WHITE) >$(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT) ---------------------------------- $(NORMAL)\n"
		@printf "        \ $(GREEN)$(BRIGHT)  ^__^$(NORMAL)\n"
		@printf "         \ $(GREEN)$(BRIGHT) (oo)\_______$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT) (__)\       )\/\$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||----w |$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||     ||$(NORMAL)\n\n"

all::	$(NAME)

d: debug

debug::
		@printf "$(CLR_TERM)$(WHITE)$(BRIGHT) ______________________________ $(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT)< Trying my best to make $(CYAN)$(DNAME)$(WHITE) >$(NORMAL)\n"
		@printf "$(WHITE)$(BRIGHT) ------------------------------ $(NORMAL)\n"
		@printf "        \ $(GREEN)$(BRIGHT)  ^__^$(NORMAL)\n"
		@printf "         \ $(GREEN)$(BRIGHT) (oo)\_______$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT) (__)\       )\/\$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||----w |$(NORMAL)\n"
		@printf "           $(GREEN)$(BRIGHT)     ||     ||$(NORMAL)\n\n"

debug::	$(DNAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIRS)
				@printf "$(YELLOW)$(BRIGHT)Generating %25s\t$(NORMAL)%40s\r" "$(NAME) src objects..." $@
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DDIR)/%.o:	$(DDIR)/%.c
				@mkdir -p $(DDIR)
				@printf "$(YELLOW)$(BRIGHT)Generating %25s\t$(NORMAL)%40s\r" "$(NAME) debug objects..." $@
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME)::	$(LIBDIR)/$(LIBNAME) $(OBJ) 
			@printf "\n$(MAGENTA)$(BRIGHT)Compiling $(NAME)...          $(NORMAL)\n"
			@$(CC) $(CFLAGS) $(OBJ) $(INC) -o $(NAME) $(LIB)
			@printf "$(GREEN)$(BRIGHT)COMPLETE!!$(NORMAL)\n\n"

$(DNAME)::	SRC:=$(filter-out $(SRC_DIR)/main.c, $(SRC))

$(DNAME)::	$(LIBDIR)/$(LIBNAME) $(SRC) $(DSRC)
			@printf "\n$(MAGENTA)$(BRIGHT)Compiling $(DNAME) for $(NAME)...          $(NORMAL)\n"
			@$(CC) $(CFLAGS) $(DFLAGS) $(INC) $(SRC) $(DSRC) -o $(DNAME) $(LIB)
			@printf "$(GREEN)$(BRIGHT)COMPLETE!!$(NORMAL)\n\n"

$(LIBDIR)/$(LIBNAME):
		@make -C $(LIBDIR) --no-print-directory

clean:
		@printf "$(RED)$(BRIGHT)Removing $(NAME) objects...\n$(NORMAL)"
		@make clean -C $(LIBDIR) --no-print-directory
		@$(RM) $(OBJ) $(DOBJ)
		@$(RM) -r $(OBJ_DIR)

fclean:	clean
		@printf "$(RED)$(BRIGHT)Deleting $(NAME) and $(DNAME)...\n\n$(NORMAL)"
		@make fclean -C $(LIBDIR) --no-print-directory
		@$(RM) $(NAME)
		@$(RM) $(DNAME)

re:			fclean all

.PHONY: all clean fclean re debug bonus norm d

norm:
		@norminette $(SRC_DIR) includes/