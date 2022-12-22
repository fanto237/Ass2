C++ = g++
CFLAGS = -Wall -Wextra -Weffc++ -pedantic -fPIE -std=c++17
C_DEBUG_FLAGS = -g
RM = /bin/rm -f
EXEC = ausgabe
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

default: $(EXEC)

$(EXEC): $(OBJ)
	$(C++) -o $(EXEC) $(OBJ)

%.o: %.cpp
	$(C++) $(C_DEBUG_FLAGS) $(CFLAGS) -MMD -c $<

-include $(SRC:.cpp=.d)

clean:
	$(RM) $(EXEC) $(OBJ) *.d
