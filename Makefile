# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcil <fcil@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 13:53:13 by aeser             #+#    #+#              #
#    Updated: 2022/07/25 10:46:19 by fcil             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRC_DIR		:= src
OBJ_DIR		:= obj

SRCS		:= $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBS		:= -lreadline

LIBFT_DIR	:= ./libs/libft
LIBFT		:= $(LIBFT_DIR)/libft.a

INCLUDE		:= -I./include
CFLAGS		:= -Wall -Wextra $(INCLUDE) $(LIBS) -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
