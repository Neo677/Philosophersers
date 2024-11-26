# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MAKEFILE                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thobenel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 16:14:44 by thobenel          #+#    #+#              #
#    Updated: 2024/11/01 16:14:45 by thobenel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Philosophers

CFLAGS = -Wall -Werror -Wextra
GCC = gcc 
# -fsanitize=thread

SRCS =	main.c init.c parsing.c write.c synchro_utils.c utils.c safe_fonction.c setters_getters.c \
		dinner_start.c monitor.c routine.c routine_utils.c solo_philo.c write_utils.c parsing_utils.c

RM = rm -f

OBJET = $(SRCS:.c=.o)

RED =	\033[0;31m
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RESET = \033[0m



.c.o:
	@echo "$(YELLOW)compilation $<...$(RESET)"
	$(GCC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJET)
	@echo "$(YELLOW)Liens executable $(NAME)...$(RESET)"
	$(GCC) $(CFLAGS) -o $(NAME) $(OBJET)
	@echo "$(GREEN)executable $(NAME) la creation est un succes!$(RESET)"

all: $(NAME)

clean:
	@echo "$(RED)remove des fichiers...$(RESET)"
	$(RM) $(OBJET)

fclean: clean
	@echo "$(RED)remove de excutable...$(RESET)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re