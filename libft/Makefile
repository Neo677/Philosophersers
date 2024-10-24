# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thobenel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 20:16:47 by thobenel          #+#    #+#              #
#    Updated: 2024/05/05 20:16:53 by thobenel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_calloc.c ft_strjoin.c \
    ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_function_printf.c \
	ft_printf.c get_next_line.c get_next_line_utils.c

BONUS = ft_lstadd_front.c ft_lstadd_back.c ft_lstnew.c ft_lstlast.c ft_lstsize.c \
		ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c
RM = rm -f 
CC = cc $(CFLAGS) 
CFLAGS = -Wall -Werror -Wextra -fPIC
SRCS_BONUS = $(BONUS) $(SRCS)
OBJS = $(SRCS:.c=.o)
OBJS_SRCS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o: 
	$(CC) $(CFLAGS) -I include -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_SRCS_BONUS)
	ar rcs $(NAME) $(OBJS_SRCS_BONUS)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_SRCS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all re clean fclean
