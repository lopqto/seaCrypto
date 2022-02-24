CC = gcc

CFLAGS  = -g -Iinclude/

TARGET = seaCrypto

.PHONY: $(TARGET)

all: $(TARGET)

$(TARGET): ./src/$(TARGET).c
	$(CC) $(CFLAGS) ./src/$(TARGET).c -o $(TARGET) ./src/base64.c ./src/rc4.c ./src/xor.c ./src/ceasar.c

clean:
	$(RM) $(TARGET)