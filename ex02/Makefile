# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samusanc <samusanc@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 19:28:25 by samusanc          #+#    #+#              #
#    Updated: 2025/05/04 13:09:06 by samusanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	scop
CXXFLAGS	=	-I ./
CXXFLAGS	+=	-std=c++17
LDFLAGS		=	-lglfw -lvulkan -ldl -lpthread 
CXX			=	g++ $(CXXFLAGS)
GLSLC		=	glslc
MAIN		=	./main.cpp
FRAG		=	./shaders/simple_shader.frag \

VERT		=	./shaders/simple_shader.vert \

INC			=	./scop.hpp \
				./device.hpp \

SRCS		=	$(MAIN) \
				./scop.cpp \
				./device.cpp \

O_DIR		=	./objects/

OBJS		=	$(addprefix $(O_DIR)/, $(SRCS:.cpp=.o))
SHADERS		=	$(VERT:.vert=.vert.spv)
SHADERS		+=	$(FRAG:.frag=.frag.spv)

$(O_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) -c $< -o $(O_DIR)/$(<:.cpp=.o)


%.vert.spv: %.vert
	$(GLSLC) $< -o $@
	@echo "VERT Shaders compiled..."

%.frag.spv: %.frag
	$(GLSLC) $< -o $@
	@echo "FRAG Shaders compiled..."


all: $(NAME) $(SRCS)

$(NAME): $(SHADERS) $(OBJS) $(INC)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

re: fclean all

fclean: clean
	@rm -f $(NAME)
	@rm -rf objects
	@rm -rf $(SHADERS)

clean:
	@rm -f $(OBJS)

.PHONY: all
