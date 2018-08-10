# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atikhono <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/01 17:15:51 by atikhono          #+#    #+#              #
#    Updated: 2018/08/10 11:29:48 by atikhono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

LIBNAME = ./libft/libft.a
LIB_DIR = libft/

OBJ = $(SRC:.c=.o)
OBJ_DIR = obj/

FLAGS = -Wfatal-errors

#-Wall -Wextra -Werror

MLX = -lmlx -framework AppKit -framework OpenGL  

OPENCL = -framework OpenCL

SRC =	main.c\
		host.c\
		hookers.c

all: liball $(NAME)

obj: $(OBJ)

$(NAME) : $(LIBNAME) $(OBJ)
		gcc -O3 $(FLAGS) $^ -o $(NAME) $(MLX) $(OPENCL)

%.o: %.c
		gcc $(FLAGS) -o $@ -c $<

clean: libclean
		rm -rf $(OBJ)

fclean: libfclean clean
		rm -rf $(NAME)

re: fclean all

$(LIBNAME): liball

liball:
	@make -C ./libft all

libclean:
	@make -C ./libft clean

libfclean:
	@make -C ./libft fclean

libre: libfclean liball
