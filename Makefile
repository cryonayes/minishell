# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeser <aeser@42kocaeli.com.tr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/26 13:53:13 by aeser             #+#    #+#              #
#    Updated: 2022/06/26 14:00:45 by aeser            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRC_DIR		:= src
OBJ_DIR		:= obj

SRCS		:= $(wildcard $(SRC_DIR)/*.c)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR	:= ./libs/libft
LIBFT		:= $(LIBFT_DIR)/libft.a

INCLUDE		:= -I./include
CFLAGS		:= -Wall -Wextra $(INCLUDE) -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
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
