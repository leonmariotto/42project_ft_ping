# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimanau <lsimanau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/14 14:00:58 by pemora            #+#    #+#              #
#    Updated: 2020/05/16 01:49:23 by lmariott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ping
CC ?= clang
CFLAGS ?= -Wall -Wextra -Werror

SRC := src/main.c\
				src/fill_hdr.c\
				src/getip.c

HDR := libft/libft.h	

HDRDIR := include/
LIBDIR := libft/

OBJ := $(SRC:.c=.o)
LIBFT := libft/libft.a
LIBS := $(LIBFT) -ltermcap

all: $(NAME) 

$(LIBFT):
	make -j 8 -C libft/

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBS) -I$(HDRDIR) -I$(LIBDIR)

%.o: %.c $(HDR) Makefile
	$(CC) $(CFLAGS) -o $@ -c $< -I$(HDRDIR) -I$(LIBDIR)

clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re
