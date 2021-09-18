CC = gcc

CFLAGS  = -g -Iinclude/

TARGET = seaCrypto

all: $(TARGET)

$(TARGET): ./src/$(TARGET).c
	$(CC) $(CFLAGS) ./src/$(TARGET).c -o $(TARGET) ./src/base64.c ./src/rc4.c

clean:
	$(RM) $(TARGET)