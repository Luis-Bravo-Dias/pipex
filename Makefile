# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lleiria- <lleiria-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 10:58:20 by lleiria-          #+#    #+#              #
#    Updated: 2022/07/25 15:32:44 by lleiria-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror 
RM			=	rm -f

NAME		=	pipex

DEPS		=	libft/libft.a ft_printf/libftprintf.a get_next_line/get_next_line.a
INCLUDE		=	 -I ft_printf/ft_printf.h -I libft/libft.h -I get_next_line/get_next_line.h -I pipex.h
SRCS_		=	main.c 

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

_OBJ		=	./obj/
_SRC		= 	./src/
OBJS		=	$(patsubst $(_SRC)%.c, $(_OBJ)%.o, $(SRCS))

all:		$(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(DEPS) $(_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME) $(DEPS)

#bonus:		$(SRCS_B) $(OBJS_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -o $(NAME_B)
#			$(CC) $(CFLAGS) $(SRCS_B) -c

libft/libft.a:
	make libft.a -C libft
ft_printf/libftprintf.a:
	make libftprintf.a -C ft_printf
get_next_line/get_next_line.a:
	make get_next_line/get_next_line.a -C get_next_line


$(_OBJ):
	mkdir $@

clean:
	make clean -C ft_printf
	make clean -C libft
	make clean -C get_next_line
	$(RM) -r $(_OBJ)

fclean:	clean
	make fclean -C ft_printf
	make fclean -C libft
	make fclean -C get_next_line
	$(RM) $(NAME)

re:	fclean all
