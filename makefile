#Variables
TARGET = project1
SRC = source.c
OBJ = $(SRC:.c=.o)
CC = gcc -g


all: $(TARGET)

#Compiles TARGET using all the OBJ files
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

#pattern rule to make all OBJ files
%.o: %.c list.h
	$(CC) -c $< -o $@

#removes all OBJ files and the EXE
clean:
	clear
	rm -f $(OBJ) $(TARGET)
