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
%.o: %.c 
	$(CC) -c $< -o $@

#removes all OBJ files and the EXE
clean:
	rm -f $(OBJ) $(TARGET)
