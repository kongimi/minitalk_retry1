# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/21 14:41:01 by npiyapan          #+#    #+#              #
#    Updated: 2024/03/02 12:03:46 by npiyapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
NAME_CLIENT = client
NAME_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

OBJ_DIR = bin/
CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBTF_DIR =  libft/
LIBFT = $(LIBTF_DIR)libft.a

HEADER = -I$(LIBTF_DIR)

SRC_FILE = server
SRC_CLIENT_FILE = client
SRC_FILE_BONUS = server_bonus
SRC_CLIENT_FILE_BONUS = client_bonus

SRC = $($(addsuffix .c, $(SRC_FILE)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILE)))
SRC_BONUS = $($(addsuffix .c, $(SRC_FILE_BONUS)))
OBJ_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILE_BONUS)))

SRC_CLIENT = $($(addsuffix .c, $(SRC_CLIENT_FILE)))
OBJ_CLIENT = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLIENT_FILE)))
SRC_CLIENT_BONUS = $($(addsuffix .c, $(SRC_CLIENT_FILE_BONUS)))
OBJ_CLIENT_BONUS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLIENT_FILE_BONUS)))

bin/%.o: %.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME) $(NAME_CLIENT)

bonus:	$(NAME_BONUS) $(NAME_CLIENT_BONUS)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBTF_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS)
	$(MAKE) -C $(LIBTF_DIR)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(MAKE) -C $(LIBTF_DIR)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
	$(MAKE) -C $(LIBTF_DIR)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)

clean:
	rm -rf bin
	rm -f $(NAME) $(NAME_CLIENT)
	rm -f $(NAME_BONUS) $(NAME_CLIENT_BONUS)
	rm -f $(LIBTF_DIR)libft.a
	$(MAKE) -C $(LIBTF_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBTF_DIR) clean

re: fclean all

.PHONY: all bonus clean fclean re
