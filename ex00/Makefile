SRCS		=	main.cpp \
				BitcoinExchange.cpp

INCL		=	BitcoinExchange.hpp

CC			=	c++

CFLAGS		=	-Wall -Werror -Wextra -std=c++98

RM			=	rm -f

NAME		=	btc

OBJ			=	$(SRCS:.cpp=.o)

all			:	$(NAME) 

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME)		:	$(OBJ) $(INCL)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
		
clean		:	
				$(RM) $(OBJ)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	clean fclean re all