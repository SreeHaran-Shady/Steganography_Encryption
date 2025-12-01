CC = gcc
CFLAGS = -Iinclude -Wall
SRC = src/main.c src/encode.c src/decode.c src/encrypt.c src/bmp_utils.c
OBJ = $(SRC:.c=.o)
TARGET = stego

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o build/$(TARGET)

clean:
	rm -f src/*.o build/$(TARGET)
