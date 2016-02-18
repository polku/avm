#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 09:44:39 by jmaurice          #+#    #+#              #
#    Updated: 2015/01/30 16:32:14 by jmaurice         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++11
DBGFLAGS = -g -Wall -Wextra -std=c++11
LDFLAGS =
INC = -I/Volumes/Data/nfs/zfs-student-2/users/2013/jmaurice/.brew/Cellar/boost/1.57.0/include
FILES = VM AParser ParserFile ParserCin OpFactory main
TPL = Operand.tpp
SRC = $(addsuffix .cpp, $(FILES))
OBJ = $(addsuffix .o, $(FILES))
NAME = avm

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ): $(SRC) $(TPL)
	$(CC) -c $(CFLAGS) $(SRC) $(INC)

debug: clean
	$(CC) -o $@ $(DBGFLAGS) $(SRC) $(INC) $(LDFLAGS)

clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f debug

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
