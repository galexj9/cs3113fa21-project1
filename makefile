#Variables
TARGET = project1
SRC = source.c list.c
OBJ = $(SRC:.c=.o)
HEAD = list.h
CC = gcc -g

all: $(TARGET)

#Compiles TARGET using all the OBJ files
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

#pattern rule to make all OBJ files
%.o: %.c $(HEAD)
	$(CC) -c $< -o $@

#removes all OBJ files and the EXE
clean:
	rm -f $(OBJ) $(TARGET)
