CC=clang++
C_FLAGS=-Wall -Wextra -Werror -std=c++98 
S_FLAGS=-g -fsanitize=address
BIN=container_test

INC=inc/

HFILE=iterator.hpp\
	vector.hpp\
	type_traits.hpp\
	utils.hpp\
	map.hpp\
	stack.hpp\
	rbTree.hpp


HDR=$(addprefix $(INC)/, $(HFILE))

SDIR=src

SFILE=container_test.cpp

SRC=$(addprefix $(SDIR)/, $(SFILE))

ODIR=obj
OFILE=$(patsubst %.cpp, %.o, $(SFILE))
OBJ=$(addprefix $(ODIR)/, $(OFILE))

.Phony: all clean fclean re run

all:$(BIN)

$(BIN): $(ODIR) $(OBJ) $(SRC) $(HDR)
	$(CC) $(C_FLAGS)  $(OBJ) -I $(INC) -o $(BIN)

$(ODIR):
	mkdir obj

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(C_FLAGS) $^ -c -o $@ -I $(INC)

clean:
	rm -fd $(OBJ) $(ODIR)

fclean:
	make clean
	rm -f $(BIN)

re:
	make fclean
	make $(BIN)

run:$(BIN)
	./$(BIN)
