# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimanau <lsimanau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/14 14:00:58 by pemora            #+#    #+#              #
#    Updated: 2020/06/29 21:46:07 by lmariott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ping
CC ?= clang
CFLAGS ?= -Wall -Wextra -Werror -g3

SRC := src/main.c\
				src/init_ping.c\
				src/resolv_addrs.c\
				src/fill_content.c\
				src/fill_hdrs.c\
				src/request_socket.c\
				src/pingloop.c\
				src/getip.c\
				src/update_icmp_seq.c\
				src/signal.c\
				src/stop_ping.c\
				src/clear_myping.c\
				src/diff_timeval.c\
				src/getopt.c

HDR := libft/libft.h	

HDRDIR := include/
LIBDIR := libft/

OBJ := $(SRC:.c=.o)
LIBFT := libft/libft.a
LIBS := $(LIBFT) -lm

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
