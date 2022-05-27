CC=c++
C_FLAGS=-Wall -Wextra -Werror -std=c++98 
S_FLAGS=-g -fsanitize=address
FTBIN=ownContainerTest
STDBIN=stlContainerTest


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
#SFILE=main.cpp
#SFILE=jstest.cpp
#SFILE=jltest.cpp

SRC=$(addprefix $(SDIR)/, $(SFILE))

ODIR=obj
OFILE=$(patsubst %.cpp, %.o, $(SFILE))
OBJ=$(addprefix $(ODIR)/, $(OFILE))

OWNOUT=ownData
STLOUT=stlData

COUNT=10

.Phony: all clean fclean re run

all:$(FTBIN) $(STDBIN)

$(FTBIN): $(ODIR) $(OBJ) $(SRC) $(HDR)
	@$(CC) $(C_FLAGS)  $(OBJ) -I $(INC) -o $(FTBIN) 

$(STDBIN): $(SRC)
	@$(CC) $(C_FLAGS) $(SRC) -o $(STDBIN)  -D STD
$(ODIR):
	@mkdir obj

$(ODIR)/%.o: $(SDIR)/%.cpp
	@$(CC) $(C_FLAGS) $^ -c -o $@ -I $(INC) -D FT

clean:
	@rm -f $(ODIR)/*
	@rm -fd $(ODIR)

fclean:
	@make clean
	@rm -f $(FTBIN) $(STDBIN) $(OWNOUT) $(STLOUT)

re:
	@make fclean
	@make $(FTBIN) $(STDBIN)

run:
	@make re
	@echo Timing own containers
	@time ./$(FTBIN) 1234 > $(OWNOUT)
	@echo ""
	@echo Timing stl containers
	@time ./$(STDBIN) 1243 > $(STLOUT)

diff:
	diff $(OWNOUT) $(STLOUT)

