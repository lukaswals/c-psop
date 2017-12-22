CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall

TARGET = psop
OBJ = algoritmoPSOP.o

#%.o: %.c $(DEPS)
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	$(RM) $(OBJ)

clean:
	$(RM) $(OBJ) $(TARGET)
