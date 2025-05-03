# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 19:28:25 by samusanc          #+#    #+#              #
#    Updated: 2025/05/03 00:43:41 by samusanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	scop
CXXFLAGS	=	-I ./
CXXFLAGS	+=	-std=c++17
LDFLAGS		=	-lglfw -lvulkan -ldl -lpthread 
CXX		=	g++ $(CXXFLAGS)
MAIN		=	./main.cpp
INC		=	./scop.hpp

SRCS		=	$(MAIN) \
				./scop.cpp \

O_DIR		=	./objects/
OBJS		=	$(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))

$(O_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) -c $< -o $(O_DIR)/$(<:.cpp=.o)

all: $(NAME) $(SRCS)

$(NAME): $(OBJS) $(INC)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

re: fclean all

fclean: clean
	@rm -f $(NAME)
	@rm -rf objects

clean:
	@rm -f $(OBJS)

.PHONY: all
